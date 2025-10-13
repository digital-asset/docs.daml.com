// Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package main

import (
	"github.com/hyperledger/fabric-chaincode-go/shim"
	"github.com/hyperledger/fabric-chaincode-go/shimtest"
	"github.com/op/go-logging"
	"math/rand"
	"testing"
)

// some of the testing code is adapted from https://medium.com/coinmonks/tutorial-on-hyperledger-fabrics-chaincode-testing-44c3f260cb2b
// run it with: go test

var testLog = logging.MustGetLogger("testing")

func checkInvoke(t *testing.T, stub *shimtest.MockStub, function string, args []string) {
	functionAndArgsAsBytes := getFunctionAndArgsAsBytes(function, args)
	res := stub.MockInvoke("1", functionAndArgsAsBytes)
	if res.Status != shim.OK {
		testLog.Infof("Invoke %s failed: %s", function, string(res.Message))
		t.FailNow()
	} else {
		testLog.Infof("Invoke %s successful: %s", function, string(res.Message))
	}
}

func checkBadInvoke(t *testing.T, stub *shimtest.MockStub, function string, args []string) {
	functionAndArgsAsBytes := getFunctionAndArgsAsBytes(function, args)
	res := stub.MockInvoke("1", functionAndArgsAsBytes)
	if res.Status == shim.OK {
		testLog.Infof("Invoke %s unexpectedly succeeded", function)
		t.FailNow()
	} else {
		testLog.Infof("Invoke %s failed as expected with message %s", function, res.Message)
	}
}

func checkQuery(t *testing.T, stub *shimtest.MockStub, function string, args []string, value string) {
	functionAndArgsAsBytes := getFunctionAndArgsAsBytes(function, args)
	res := stub.MockInvoke("1", functionAndArgsAsBytes)
	if res.Status != shim.OK {
		testLog.Infof("Query %s failed: %s", function, string(res.Message))
		t.FailNow()
	}
	if res.Payload == nil {
		testLog.Infof("Query %s failed to get value", function)
		t.FailNow()
	}
	payload := string(res.Payload)
	if payload != value {
		testLog.Infof("Query value %s was %s and not %s as expected", function, payload, value)
		t.FailNow()
	} else {
		testLog.Infof("Query value %s is %s as expected", function, payload)
	}
}

func getFunctionAndArgsAsBytes(function string, args []string) [][]byte {
	bytes := make([][]byte, 0, len(args)+1)
	bytes = append(bytes, []byte(function))
	for _, s := range args {
		bytes = append(bytes, []byte(s))
	}
	return bytes
}

func randomString(n int) string {
	var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
	s := make([]rune, n)
	for i := range s {
		s[i] = letters[rand.Intn(len(letters))]
	}
	return string(s)
}

const TRACE_ID = "00-0af7651916cd43dd8448eb211c80319c-b9c7c989f97918e1-01"

func TestRegisterMember(t *testing.T) {
	chaincode := new(sequencerChaincode)
	mockStub := shimtest.NewMockStub("Sequencer", chaincode)

	// register member and then it can be queried
	checkQuery(t, mockStub, "allMembers", []string{TRACE_ID}, "")
	checkInvoke(t, mockStub, "registerMember", []string{TRACE_ID, "m1"})
	checkQuery(t, mockStub, "allMembers", []string{TRACE_ID}, "m1")

	// missing member argument
	checkBadInvoke(t, mockStub, "registerMember", []string{TRACE_ID})

	// member string can be at most 300 characters long
	checkInvoke(t, mockStub, "registerMember", []string{TRACE_ID, randomString(300)})
	checkBadInvoke(t, mockStub, "registerMember", []string{TRACE_ID, randomString(301)})
}

func TestSend(t *testing.T) {
	chaincode := new(sequencerChaincode)
	mockStub := shimtest.NewMockStub("Sequencer", chaincode)
	uuid1 := "ec9c4fd6-61b0-426d-be53-e9a08852f370"
	uuid2 := "af4ef923-62a1-4432-9ec9-66b1a9fc5a6d"
	uuid3 := "f76612d-7486-4386-ba4d-c19313fef21b"
	uuid4 := "21b8793c-d07d-4b1e-a40b-33408cdb3933"

	checkInvoke(t, mockStub, "send", []string{TRACE_ID, uuid1, "123456", "submission"})

	// reusing same uuid will fail
	checkBadInvoke(t, mockStub, "send", []string{TRACE_ID, uuid1, "123456", "submission"})

	// uuid size is 36
	checkInvoke(t, mockStub, "send", []string{TRACE_ID, randomString(36), "123456", "submission"})
	checkBadInvoke(t, mockStub, "send", []string{TRACE_ID, randomString(37), "123456", "submission"})
	checkBadInvoke(t, mockStub, "send", []string{TRACE_ID, randomString(35), "123456", "submission"})
	checkBadInvoke(t, mockStub, "send", []string{TRACE_ID, "", "123456", "submission"})

	// timestamp microseconds should be a long
	checkInvoke(t, mockStub, "send", []string{TRACE_ID, uuid2, "9223372036854775807", "submission"})
	// this is is bigger than max long
	checkBadInvoke(t, mockStub, "send", []string{TRACE_ID, uuid3, "9223372036854775808", "submission"})
	// timestamp microseconds fails if not a number
	checkBadInvoke(t, mockStub, "send", []string{TRACE_ID, uuid4, "notANumber", "submission"})
}

func TestCannotInvokeInvalidFunction(t *testing.T) {
	chaincode := new(sequencerChaincode)
	mockStub := shimtest.NewMockStub("Sequencer", chaincode)

	checkBadInvoke(t, mockStub, "invalidFunction", []string{TRACE_ID})
}

func TestTraceId(t *testing.T) {
	chaincode := new(sequencerChaincode)
	mockStub := shimtest.NewMockStub("Sequencer", chaincode)

	// trace id must have size 55
	checkBadInvoke(t, mockStub, "registerMember", []string{TRACE_ID + "1", "m1"})
	checkBadInvoke(t, mockStub, "registerMember", []string{"garbage", "m1"})
	// not using tracing is allowed by passing empty string
	checkInvoke(t, mockStub, "registerMember", []string{"", "m1"})
}

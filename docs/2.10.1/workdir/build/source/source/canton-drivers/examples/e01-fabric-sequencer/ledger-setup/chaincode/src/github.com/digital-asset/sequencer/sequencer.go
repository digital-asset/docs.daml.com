// Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package main

import (
	"fmt"
	"strconv"
	"strings"

	"github.com/hyperledger/fabric-chaincode-go/shim"
	pb "github.com/hyperledger/fabric-protos-go/peer"
	"github.com/op/go-logging"
)

type sequencerChaincode struct{}

var logger = logging.MustGetLogger("sequencer")

const (
	MAX_MEMBER_LENGTH  = 300 // max string size for member defined in canton
	UUID_LENGTH        = 36  // java uuid length
	TRACEPARENT_LENGTH = 55  // size of w3 traceparent header, which we're using here as trace-id coming from the fabric sequencer
)

// Init is called during chaincode instantiation to initialize any
// data. Note that chaincode upgrade also calls this function to reset
// or to migrate data.
func (t *sequencerChaincode) Init(stub shim.ChaincodeStubInterface) pb.Response {
	// Return the result as success payload
	return shim.Success([]byte("Successfully initialized chaincode"))
}

// Invoke is called per transaction on the chaincode. Each transaction is
// either a 'get' or a 'set' on the asset created by Init function. The Set
// method may create a new asset by specifying a new key-value pair.
func (t *sequencerChaincode) Invoke(stub shim.ChaincodeStubInterface) pb.Response {
	// Extract the function and args from the transaction proposal
	fn, allArgs := stub.GetFunctionAndParameters()

	var result string
	var err error

	if len(allArgs) == 0 {
		err = fmt.Errorf("No arguments passed. Expecting at least the trace id.")
	}

	traceContextCorrelationId := allArgs[0]
	args := allArgs[1:] // args without the trace context

	if traceContextCorrelationId != "" && len(traceContextCorrelationId) != TRACEPARENT_LENGTH {
		err = fmt.Errorf("Set trace id must have size %d", TRACEPARENT_LENGTH)
	} else {
		switch fn {
		case "registerMember":
			result, err = registerMember(stub, args)
		case "disableMember":
			result, err = disableMember(stub, args)
		case "allMembers":
			result, err = getMembersAsString(stub)
		case "isMemberRegistered":
			result, err = isMemberRegisteredAsString(stub, args)
		case "send":
			result, err = send(stub, args)
		case "getSubmissionRequest":
			result, err = getSubmissionRequest(stub, args)
		case "acknowledge":
			result, err = acknowledge(stub, args)
		case "keysToBePrunedAt":
			result, err = keysToBePrunedAt(stub, args)
		case "prune":
			result, err = prune(stub, args)
		default:
			err = fmt.Errorf("Invalid function %s", fn)
		}
	}

	if err != nil {
		logger.Errorf("%s Error invoking Sequencer chaincode fn: %s, error:", traceContextCorrelationId, fn, err)
		return shim.Error(err.Error())
	}

	logger.Infof("%s Successfully invoked Sequencer chaincode fn %s", traceContextCorrelationId, fn)
	// Return the result as success payload
	return shim.Success([]byte(result))

}

type chaincodeRunner struct{}

// this var is what we load when we use this file as a compile plugin. exported as symbol named "Sequencer"
var Sequencer chaincodeRunner

func (r chaincodeRunner) Run() {
	if err := shim.Start(new(sequencerChaincode)); err != nil {
		logger.Errorf("Error starting Sequencer chaincode: %s", err)
	}
}

// expects encoded member string
func registerMember(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 1 {
		return "", fmt.Errorf("Incorrect arguments. Expecting a member")
	}

	newMember := args[0]

	if len(newMember) > MAX_MEMBER_LENGTH {
		return "", fmt.Errorf("Incorrect arguments. Member length should not exceed %d characters.", MAX_MEMBER_LENGTH)
	}

	key, keyErr := stub.CreateCompositeKey("sequencer", []string{"registered-members", newMember})
	if keyErr != nil {
		return "", fmt.Errorf("Failed to create composite key for member %s: %s", newMember, keyErr)
	}

	saveMemberErr := stub.PutState(key, []byte(newMember))
	if saveMemberErr != nil {
		return "", fmt.Errorf("Failed to register member %s with error: %s", newMember, saveMemberErr)
	}

	return "Success", nil
}

func disableMember(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 1 {
		return "", fmt.Errorf("Incorrect arguments. Expecting a member")
	}
	member := args[0]

	key, keyErr := stub.CreateCompositeKey("sequencer", []string{"registered-members", member})
	if keyErr != nil {
		return "", fmt.Errorf("Failed to create composite key for member %s: %s", member, keyErr)
	}

	delMemberErr := stub.DelState(key)
	if delMemberErr != nil {
		return "", fmt.Errorf("Failed to disable member %s with error: %s", member, delMemberErr)
	}

	return "Success", nil
}

func getMembersAsString(stub shim.ChaincodeStubInterface) (string, error) {
	members, err := getMembers(stub)
	if err != nil {
		return "", err
	}
	return strings.Join(members, ", "), nil
}

func getMembers(stub shim.ChaincodeStubInterface) ([]string, error) {
	iterator, err := stub.GetStateByPartialCompositeKey("sequencer", []string{"registered-members"})
	if err != nil {
		return nil, fmt.Errorf("Failed to get registered members with error: %s", err)
	}
	members := make([]string, 0)
	for iterator.HasNext() {
		result, iteratorError := iterator.Next()
		if iteratorError != nil {
			return nil, fmt.Errorf("Failed to get registered members with error: %s", iteratorError)
		}
		member := string(result.GetValue())
		members = append(members, member)
	}
	iterator.Close()
	return members, nil
}

func isMemberRegisteredAsString(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 1 {
		return "", fmt.Errorf("Incorrect arguments. Expecting a member")
	}
	newMember := args[0]
	result, err := isMemberRegistered(stub, newMember)
	return strconv.FormatBool(result), err
}

func isMemberRegistered(stub shim.ChaincodeStubInterface, member string) (bool, error) {
	key, keyErr := stub.CreateCompositeKey("sequencer", []string{"registered-members", member})
	if keyErr != nil {
		return false, fmt.Errorf("Failed to create composite key for member %s: %s", member, keyErr)
	}
	value, getMemberErr := stub.GetState(key)
	if getMemberErr != nil {
		return false, fmt.Errorf("Failed to query for member %s with error: %s", member, getMemberErr)
	}
	return value != nil, nil
}

func privateDataSubmissionRequestKey(timestampMicros string, uuid string) string {
	if uuid == "" {
		return fmt.Sprintf("sequencer.requests.%s", timestampMicros)
	} else {
		return fmt.Sprintf("sequencer.requests.%s.%s", timestampMicros, uuid)
	}
}

// expects:
// 1 - uuid string which should be unique across different sends
// 2 - microseconds from epoch which represents the timestamp of the event from the originating sequencer's clock
// 3 - the submission request payload. if it is missing, we look for it in the transient data and assume it has
//
//	to be saved in a private data collection.
func send(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if (len(args)) == 3 {
		uuid := args[0]
		timestampMicros := args[1]

		if len(uuid) != UUID_LENGTH {
			return "", fmt.Errorf("Incorrect arguments. UUID length should be %d characters.", UUID_LENGTH)
		}
		if _, err := strconv.ParseInt(timestampMicros, 10, 64); err != nil {
			return "", fmt.Errorf("Incorrect arguments. Timestamp microseconds should be an integer number.")
		}

		submissionRequest := args[2]

		key, keyErr := stub.CreateCompositeKey("sequencer", []string{"requests", uuid})
		if keyErr != nil {
			return "", fmt.Errorf("Failed to create submission request composite key for uuid %s: %s", uuid, keyErr)
		}

		// not allow uuid to be reused
		value, getErr := stub.GetState(key)
		if getErr != nil {
			return "", fmt.Errorf("Failed to check if there already exists a value for composite key for uuid %s: %s", uuid, getErr)
		}
		if value != nil {
			return "", fmt.Errorf("There already exists a value for composite key for uuid %s. Please use another uuid", uuid)
		}

		// we actually reconstruct the request from the parameters of the chaincode so we don't need to save the timestamp as state
		saveRequestErr := stub.PutState(key, []byte(submissionRequest))
		if saveRequestErr != nil {
			return "", fmt.Errorf("Failed to save new submission request with uuid %s with error: %s", uuid, saveRequestErr)
		}
	} else if (len(args)) == 2 {
		// if the submission request is not passed as an argument, we assume that it is passed as transient data and that
		// we want to store it in a private data collection

		uuid := args[0]
		timestampMicros := args[1]

		if len(uuid) != UUID_LENGTH {
			return "", fmt.Errorf("Incorrect arguments. UUID length should be %d characters.", UUID_LENGTH)
		}
		if _, err := strconv.ParseInt(timestampMicros, 10, 64); err != nil {
			return "", fmt.Errorf("Incorrect arguments. Timestamp microseconds should be an integer number.")
		}

		key := privateDataSubmissionRequestKey(timestampMicros, uuid)
		transMap, err := stub.GetTransient()
		if err != nil {
			return "", fmt.Errorf("Error getting transient data: %s", err.Error())
		}
		submissionRequest, exists := transMap["submissionRequest"]
		if !exists {
			return "", fmt.Errorf("Expected the submission request to have been passed as transient data ")
		}
		saveRequestErr := stub.PutPrivateData("submissionRequests", key, []byte(submissionRequest))
		if saveRequestErr != nil {
			return "", fmt.Errorf("Failed to save new submission request with uuid %s with error: %s", uuid, saveRequestErr)
		}
	} else {
		return "", fmt.Errorf("Incorrect arguments. Expecting an uuid, timestamp and a submission request")
	}

	return "Successfully sent submission request", nil
}

func getSubmissionRequest(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 2 {
		return "", fmt.Errorf("Incorrect arguments. Expecting an uuid and a timestamp")
	}
	uuid := args[0]
	timestampMicros := args[1]
	key := privateDataSubmissionRequestKey(timestampMicros, uuid)
	value, err := stub.GetPrivateData("submissionRequests", key)
	if err != nil {
		return "", fmt.Errorf("Failed to get submission request: %s with error: %s", uuid, err)
	}
	if value == nil {
		return "", fmt.Errorf("Submission request not found: %s", uuid)
	}

	return string(value), nil
}

func keysToBePrunedAt(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 1 {
		return "", fmt.Errorf("Incorrect arguments. Expecting a timestamp")
	}
	timestampMicros := args[0]

	startKey := privateDataSubmissionRequestKey("", "")
	endKey := privateDataSubmissionRequestKey(timestampMicros, "")

	resultsIterator, err := stub.GetPrivateDataByRange("submissionRequests", startKey, endKey)
	if err != nil {
		return "", fmt.Errorf("Failed to create pruning iterator for timestamp %s: %s", timestampMicros, err)
	}
	defer resultsIterator.Close()

	idsForPruning := []string{}

	for resultsIterator.HasNext() {
		response, err1 := resultsIterator.Next()
		if err1 != nil {
			return "", fmt.Errorf("Failed to iterate submission requests to be pruned: %s", err1)
		}
		idsForPruning = append(idsForPruning, response.Key)
	}

	return strings.Join(idsForPruning[:], ","), nil
}

func prune(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 2 {
		return "", fmt.Errorf("Incorrect arguments. Expecting a timestamp and the keys to be deleted")
	}

	keysString := args[1]
	if len(keysString) == 0 {
		return "0", nil
	}
	keys := strings.Split(keysString, ",")

	for _, key := range keys {
		err := stub.DelPrivateData("submissionRequests", key)
		if err != nil {
			return "", fmt.Errorf("Failed to delete private data at key %s: %s", key, err)
		}
	}
	return fmt.Sprintf("%d", len(keys)), nil
}

func acknowledge(stub shim.ChaincodeStubInterface, args []string) (string, error) {
	if len(args) != 2 && len(args) != 1 {
		return "", fmt.Errorf("Incorrect arguments. Expecting a member and a timestamp or a signed acknowledge request")
	}
	return "Successfully acknowledged", nil
}

// main function starts up the chaincode in the container during instantiate
// this main does not get called if this file is used a compile plugin. instead the file using this plugin will call
// Sequencer.Run() from its main method
func main() {
	Sequencer.Run()
}

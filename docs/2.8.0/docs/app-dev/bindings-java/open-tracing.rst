.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _open-tracing-ledger-api-client:

Open Tracing in Ledger API Client Applications
##############################################

Introduction
============

Distributed tracing is a technique used for troubleshooting performance issues in a microservices environment like Daml Enterprise. Tracing in Canton has been described in a :ref:`page dedicated to monitoring <tracing>`. Current article describes how to write **Ledger API** client applications so that distributed traces and spans can seamlessly continue between the client and Canton software components.

To study in detail a **Ledger API** client application with OpenTelemetry support, see an `example on GitHub <https://github.com/digital-asset/ex-java-bindings-with-opentelemetry>`__.

The example implements a variation of the already familiar ``PingPong`` application, where every call to the **Ledger API** is decorated with an OpenTelemetry trace context. Additionally, it demonstrates how to retrieve the trace context from the past transactions.

If you want to familiarize yourself with the broader topic of open tracing you can start by consulting the official pages of `the OpenTelemetry project <https://opentelemetry.io/>`_. To find out more about java specifically, the documentation on `java OpenTelemetry instrumentation <https://opentelemetry.io/docs/instrumentation/java/>`_ is an excellent source of references and examples.


Setting up OpenTelemetry Server
===============================

In order to be able to observe the distributed tracing in action, you will need to start an OpenTelemetry backend server. Jaeger, zipkin or OTLP formats are all supported by Canton. To start a jager server you can use the following docker command

::

    docker run --rm -it --name jaeger\
      -p 16686:16686 \
      -p 14250:14250 \
      jaegertracing/all-in-one:1.22.0

Adding Project Dependencies
===========================

To use the OpenTelemetry libraries, add the following **Maven** dependencies to your project's ``pom.xml``:

::

    <dependency>
      <groupId>io.opentelemetry</groupId>
      <artifactId>opentelemetry-api</artifactId>
      <version>x.y.z</version>
    </dependency>
    <dependency>
      <groupId>io.opentelemetry</groupId>
      <artifactId>opentelemetry-sdk</artifactId>
      <version>x.y.z</version>
    </dependency>
    <dependency>
      <groupId>io.opentelemetry</groupId>
      <artifactId>opentelemetry-exporter-jaeger</artifactId>
      <version>x.y.z</version>
    </dependency>
    <dependency>
      <groupId>io.opentelemetry.instrumentation</groupId>
      <artifactId>opentelemetry-grpc-1.6</artifactId>
      <version>x.y.z</version>
    </dependency>

.. note::
    Replace ``x.y.z`` for both dependencies with the version that you want to use. You can find the available versions by checking the `Maven Central Repository <https://search.maven.org/artifact/io.opentelemetry/opentelemetry-api>`__ etc.


Initializing
============

An application that wants to use OpenTelemetry must initialize a number of global controller objects that orchestrate different aspects of the distributed tracing process such as span creation, propagation and export. The exact set of the controllers needed may vary fom application to application. You may draw some inspiration from the selection used in the example inside `the OpenTelemetryUtil.createOpenTelemetry method <https://github.com/digital-asset/ex-java-bindings-with-opentelemetry/blob/master/src/main/java/examples/pingpong/codegen/OpenTelemetryUtil.java>`_. This is the minimum set required for a fully functional jaeger trace reporting.

The next step is to initialize the GrpcTelemetry controller, which is responsible for propagation of the trace contexts inside the HTTP2 headers of the Grpc communication.

Conveniently, the example wraps the necessary initialization steps in the constructor of the OpenTelemetryUtil class. All you have to do is call

.. code-block:: java

    OpenTelemetryUtil openTelemetry = new OpenTelemetryUtil(APP_ID);

The GrpcTelemetry controller can construct client call interceptors that need to be mounted on top of the **Netty** channels used in the grpc communication. The example provides a useful helper method called ``withClientInterceptor`` that injects an interceptor at channel builder level

.. code-block:: java

    ManagedChannel channel =
      openTelemetry.withClientInterceptor(
        ManagedChannelBuilder
          .forAddress(host, port)
          .usePlaintext()
      ).build();

And with that, you are all set to start generating own spans, reporting them to the **Jaeger** server and also propagating them transparently to the **Ledger API**.

Starting New Spans
==================

Before making a Grpc call, you must generate a new span that will cover the multi-component interaction that is about to be initiated. The example provides a useful combinator called ``runInNewSpan`` that wraps the execution of an arbitrary function in a newly generated span

.. code-block:: java

    public <R> R runInNewSpan(String spanName, Supplier<R> body) {
        Span span = tracer.spanBuilder(spanName).startSpan();
        try(Scope ignored = span.makeCurrent()) {
            return body.get();
        } finally {
            span.end();
        }
    }

You can use it on a command submission in the following manner

.. code-block:: java

    openTelemetry.runInNewSpan("createInitialContracts", () -> submissionService.submit(request));

The Grpc interceptors that have been mounted at the initialization stage, will do the rest of the work behind the scenes making sure that the spans make it across to the Canton.

Continuing Spans Across Different Applications
==============================================

Sometimes, you may wish to continue the same span across multiple daml transactions forming a single workflow. This may be especially interesting when different client application instances interact through the ledger and yet their entire conversation should be seen as a single coherent succession of spans. In that case, it is possible to extract the trace context associated with the past transactions from the Transaction, TransactionTree or Completion records that are returned from the following **Ledger API** calls

* TransactionService.GetTransactions
* TransactionService.GetTransactionTrees
* TransactionService.GetTransactionByEventId
* TransactionService.GetTransactionById
* TransactionService.GetFlatTransactionByEventId
* TransactionService.GetFlatTransactionById
* CompletionService.CompletionStream

You can extract the context by using a helper function implemented in the example

.. code-block:: java

    Context extractedContext = openTelemetry.contextFromDamlTraceContext(tx.getTraceContext());

The extracted context has to be elevated to the status of the current context. Doing this allows the continuation of the original trace context into the present operation. Again the example provides a convenient combinator for that

.. code-block:: java

    openTelemetry.runInOpenTelemetryScope(extractedContext, () -> ... );

Finally, you generate a new span within the original context. You can use the already familiar ``runInNewSpan`` method

.. code-block:: java

    openTelemetry.runInNewSpan("follow", () ->
      submissionService.submit(SubmitRequest.toProto(ledgerId, commandsSubmission))
    )
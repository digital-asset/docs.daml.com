// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.nightly

import com.digitalasset.canton.concurrent.FutureSupervisor
import com.digitalasset.canton.config.KmsConfig
import com.digitalasset.canton.crypto.kms.aws.AwsKms
import com.digitalasset.canton.crypto.kms.driver.api.v1.{
  EncryptionKeySpec,
  KmsDriver,
  SigningKeySpec,
}
import com.digitalasset.canton.crypto.kms.driver.testing.v1.{KmsDriverFactoryTest, KmsDriverTest}
import com.digitalasset.canton.crypto.kms.driver.v1.DriverKms
import com.digitalasset.canton.crypto.kms.driver.v1.aws.{
  AwsKmsDriver,
  AwsKmsDriverConfig,
  AwsKmsDriverFactory,
}
import com.digitalasset.canton.crypto.provider.kms.HasPredefinedAwsKmsKeys
import org.scalatest.wordspec.FixtureAsyncWordSpec
import pureconfig.ConfigWriter

import scala.annotation.nowarn

/** Implements the test using our internal test suite for KMS */
class AwsKmsDriverInternalTest
    extends FixtureAsyncWordSpec
    with ExternalKmsTest
    with HasPredefinedAwsKmsKeys {

  override type KmsType = DriverKms

  override lazy val kmsClient: DriverKms = {
    import pureconfig.generic.auto.*

    @nowarn("cat=lint-byname-implicit") // https://github.com/scala/bug/issues/12072
    val awsConfig = ConfigWriter[KmsConfig.Aws].to(KmsConfig.Aws.awsTestConfig)

    val driverConfig = KmsConfig.Driver("aws-kms", awsConfig)
    DriverKms
      .create(
        driverConfig,
        FutureSupervisor.Noop,
        wallClock,
        timeouts,
        loggerFactory,
        parallelExecutionContext,
      )
      .valueOrFail("Failed to create Driver KMS")
  }

  "AWS KMS Driver" must {
    behave like kms()
  }

}

/** Implements the test with the external test suite for Kms Drivers. */
// user-manual-entry-begin: AwsKmsDriverWithPredefinedKeysTest
class AwsKmsDriverWithPredefinedKeysTest extends KmsDriverTest {

  override val predefinedSigningKeys: Map[SigningKeySpec, String] =
    Map(
      SigningKeySpec.EcP256 -> "alias/canton-kms-test-signing-key",
      SigningKeySpec.EcP384 -> "alias/canton-kms-test-signing-key-P384",
    )

  override val predefinedEncryptionKeys: Map[EncryptionKeySpec, String] =
    Map(EncryptionKeySpec.Rsa2048 -> "alias/canton-kms-test-asymmetric-key")

  override val predefinedSymmetricKey: Option[String] = Some("alias/canton-kms-test-key")

  override protected def newKmsDriver(): KmsDriver = {
    val awsKms = AwsKms
      .create(KmsConfig.Aws.awsTestConfig, timeouts, loggerFactory)
      .valueOrFail("failed to create AWS KMS")

    new AwsKmsDriver(awsKms)
  }

  "AWS KMS Driver" must {
    behave like kmsDriver(allowKeyGeneration = false)
  }

}
// user-manual-entry-end: AwsKmsDriverWithPredefinedKeysTest

// user-manual-entry-begin: AwsKmsDriverTest
class AwsKmsDriverTest extends KmsDriverTest {

  override protected def newKmsDriver(): KmsDriver = {
    val awsKms = AwsKms
      .create(KmsConfig.Aws.awsTestConfig, timeouts, loggerFactory)
      .valueOrFail("failed to create AWS KMS")

    new AwsKmsDriver(awsKms)
  }

  "AWS KMS Driver" must {
    behave like kmsDriver(allowKeyGeneration = true)
  }

}
// user-manual-entry-end: AwsKmsDriverTest

// user-manual-entry-begin: AwsKmsDriverFactoryTest
class AwsKmsDriverFactoryTest extends KmsDriverFactoryTest {

  override type Factory = AwsKmsDriverFactory

  override protected lazy val factory: AwsKmsDriverFactory =
    new AwsKmsDriverFactory

  override protected lazy val config: AwsKmsDriverFactory#ConfigType = {
    val aws = KmsConfig.Aws.awsTestConfig
    AwsKmsDriverConfig(region = aws.region, multiRegionKey = aws.multiRegionKey)
  }

  "AWS KMS Driver Factory" must {
    behave like kmsDriverFactory()
  }
}
// user-manual-entry-end: AwsKmsDriverFactoryTest

/**
 * Copyright (C) 2014 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

package com.virgilsecurity {

    import flash.utils.ByteArray;

    import org.hamcrest.*;
    import org.hamcrest.core.*;
    import org.hamcrest.object.*;
    import org.hamcrest.collection.*;

    import com.hurlant.util.Hex;

    import com.virgilsecurity.*;
    import com.virgilsecurity.wrapper.CModule;

    public class VirgilStreamCipherTest {
        private var cipher_:VirgilStreamCipher;

        private static const TEST_EC_PUBLIC_KEY : String =
                "-----BEGIN PUBLIC KEY-----\n" +
                "MIGbMBQGByqGSM49AgEGCSskAwMCCAEBDQOBggAEa+CTMPBSOFoeZQIPiUOc84r2\n" +
                "BsdPwOzDshzW/JDeY85E8HC+cVF/9K+vdsoeyYP3yGpTwA53hZIKueUh+QAF53C9\n" +
                "X6uaP98Jiu8RMZNplo9p4BZpCwP90A2rxRSatEFHOOtw3FCCmHqzsxpEQCEwnd47\n" +
                "BOP7sd6Nwy37YlX95RM=\n" +
                "-----END PUBLIC KEY-----\n";
        private static const TEST_EC_PRIVATE_KEY : String =
                "-----BEGIN EC PRIVATE KEY-----\n" +
                "MIHaAgEBBEBKFx+SNvhRVb0HpyEBceoVoU4AKZLrx9jdxRdQAS9tC/CQdAmB2t0h\n" +
                "XsMEbtg5DVmwh29GzuLkyTh9VQYxAP/roAsGCSskAwMCCAEBDaGBhQOBggAEa+CT\n" +
                "MPBSOFoeZQIPiUOc84r2BsdPwOzDshzW/JDeY85E8HC+cVF/9K+vdsoeyYP3yGpT\n" +
                "wA53hZIKueUh+QAF53C9X6uaP98Jiu8RMZNplo9p4BZpCwP90A2rxRSatEFHOOtw\n" +
                "3FCCmHqzsxpEQCEwnd47BOP7sd6Nwy37YlX95RM=\n" +
                "-----END EC PRIVATE KEY-----\n";
        private static const TEST_RSA_PUBLIC_KEY : String =
                "-----BEGIN PUBLIC KEY-----\n" +
                "MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAMk/B8TlOOwNnxpOBGUo0bW9HbNuiaro\n" +
                "K+GG5ZcLA9AnA2Fwkx8hFozP0hQp97kbA/RS96/NdbreSjVqltlotc0CAwEAAQ==\n" +
                "-----END PUBLIC KEY-----\n";
        private static const TEST_RSA_PRIVATE_KEY : String =
                "-----BEGIN RSA PRIVATE KEY-----\n" +
                "MIIBOQIBAAJBAMk/B8TlOOwNnxpOBGUo0bW9HbNuiaroK+GG5ZcLA9AnA2Fwkx8h\n" +
                "FozP0hQp97kbA/RS96/NdbreSjVqltlotc0CAwEAAQJAYML8olAwoVcfU8+FT3pj\n" +
                "8sU+faK9cL53MtXgmFJEgBUWlg0aGq67an8vgReCdIK6F3500f6Yf9LhjkoZ4ZBl\n" +
                "QQIhAPvyiVFhizURqzZHn4cQtKR2bgGJsARdvlg6KKHP/XXRAiEAzHu3uJ1mIFHH\n" +
                "MGMrpKC4mcnyvM4UEETIINUA+pabMz0CIGeJQA0FfOOOI0HnJROoNdPwJzzSjFb+\n" +
                "/x3aqJ/2jT5BAiBTLEtpY1Rj9v9/VgctelY776G1XFla2K9Sc3FnfBT6vQIgJlqb\n" +
                "tFCwQZczpa/OtOqYKHHpFevnLEVWrlHvCRgJeJU=\n" +
                "-----END RSA PRIVATE KEY-----\n";

        private static const TEST_PASSWORD : String = "password";

        private static const TEST_PLAIN_TEXT : String = "This string will be encrypted.";

        [BeforeClass(description = "Init library")]
        public static function setup():void {
            CModule.startAsync();
        }

        [Before(description="Creates VirgilStreamCipher object and stores it in the 'cipher_' variable.")]
        public function create_cipher() : void {
            cipher_ = VirgilStreamCipher.create();
            assertThat(cipher_.cPtr, not(equalTo(0)));
        }

        [After(description="Destroy VirgilStreamCipher object stored it in the 'cipher_' variable.")]
        public function destroy_cipher() : void {
            cipher_.destroy();
            cipher_ = null;
        }

        [Test(description="Test VirgilStreamCipher.encrypt() and VirgilStreamCipher.decrypt().")]
        public function test_cipher_encrypt_decrypt():void {
            var plainTextDataSource:VirgilDataSourceWrapper =
                    new VirgilDataSourceWrapper(ConvertionUtils.asciiStringToArray(TEST_PLAIN_TEXT));

            var encryptedText:ByteArray = new ByteArray();
            var encryptedTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(encryptedText);

            var encryptionKey:ByteArray = cipher_.encrypt(plainTextDataSource, encryptedTextDataSink,
                    ConvertionUtils.asciiStringToArray(TEST_EC_PUBLIC_KEY));

            encryptedText.position = 0;
            var encryptedTextDataSource:VirgilDataSourceWrapper = new VirgilDataSourceWrapper(encryptedText);

            var plainText:ByteArray = new ByteArray();
            var plainTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(plainText);

            cipher_.decrypt(encryptedTextDataSource, plainTextDataSink, encryptionKey,
                    ConvertionUtils.asciiStringToArray(TEST_EC_PRIVATE_KEY));

            assertThat(ConvertionUtils.arrayToAsciiString(plainText), equalTo(TEST_PLAIN_TEXT));
        }

        [Test(description="Test VirgilStreamCipher.generateKeyPair(), VirgilStreamCipher.encrypt(), VirgilStreamCipher.decrypt().")]
        public function test_cipher_encrypt_decrypt_with_generated_keys():void {
            var keyPair:VirgilKeyPair = cipher_.generateKeyPair();

            var plainTextDataSource:VirgilDataSourceWrapper =
                    new VirgilDataSourceWrapper(ConvertionUtils.asciiStringToArray(TEST_PLAIN_TEXT));

            var encryptedText:ByteArray = new ByteArray();
            var encryptedTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(encryptedText);

            var encryptionKey:ByteArray =
                    cipher_.encrypt(plainTextDataSource, encryptedTextDataSink, keyPair.publicKey());

            encryptedText.position = 0;
            var encryptedTextDataSource:VirgilDataSourceWrapper = new VirgilDataSourceWrapper(encryptedText);

            var plainText:ByteArray = new ByteArray();
            var plainTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(plainText);

            cipher_.decrypt(encryptedTextDataSource, plainTextDataSink, encryptionKey, keyPair.privateKey());

            assertThat(ConvertionUtils.arrayToAsciiString(plainText), equalTo(TEST_PLAIN_TEXT));
        }

        [Test(description="Test VirgilStreamCipher.encrypt(), VirgilStreamCipher.decrypt() and VirgilStreamCipher.reencryptKey().")]
        public function test_cipher_reencryptKey():void {
            var plainTextDataSource:VirgilDataSourceWrapper =
                    new VirgilDataSourceWrapper(ConvertionUtils.asciiStringToArray(TEST_PLAIN_TEXT));

            var encryptedText:ByteArray = new ByteArray();
            var encryptedTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(encryptedText);

            var encryptionKey:ByteArray = cipher_.encrypt(plainTextDataSource, encryptedTextDataSink,
                    ConvertionUtils.asciiStringToArray(TEST_EC_PUBLIC_KEY));
            var sharedEncryptionKey:ByteArray = cipher_.reencryptKey(encryptionKey,
                    ConvertionUtils.asciiStringToArray(TEST_RSA_PUBLIC_KEY),
                    ConvertionUtils.asciiStringToArray(TEST_EC_PRIVATE_KEY));

            encryptedText.position = 0;
            var encryptedTextDataSource:VirgilDataSourceWrapper = new VirgilDataSourceWrapper(encryptedText);

            var plainText:ByteArray = new ByteArray();
            var plainTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(plainText);

            cipher_.decrypt(encryptedTextDataSource, plainTextDataSink, sharedEncryptionKey,
                    ConvertionUtils.asciiStringToArray(TEST_RSA_PRIVATE_KEY));

            assertThat(ConvertionUtils.arrayToAsciiString(plainText), equalTo(TEST_PLAIN_TEXT));
        }

        [Test(description="Test VirgilStreamCipher.encryptWithPassword(), VirgilStreamCipher.decryptWithPassword.")]
        public function test_cipher_encrypt_decrypt_with_password():void {
            var plainTextDataSource:VirgilDataSourceWrapper =
                    new VirgilDataSourceWrapper(ConvertionUtils.asciiStringToArray(TEST_PLAIN_TEXT));

            var encryptedText:ByteArray = new ByteArray();
            var encryptedTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(encryptedText);

            cipher_.encryptWithPassword(
                    plainTextDataSource, encryptedTextDataSink,
                    ConvertionUtils.asciiStringToArray(TEST_PASSWORD));

            encryptedText.position = 0;
            var encryptedTextDataSource:VirgilDataSourceWrapper = new VirgilDataSourceWrapper(encryptedText);

            var plainText:ByteArray = new ByteArray();
            var plainTextDataSink:VirgilDataSinkWrapper = new VirgilDataSinkWrapper(plainText);

            cipher_.decryptWithPassword(encryptedTextDataSource, plainTextDataSink,
                    ConvertionUtils.asciiStringToArray(TEST_PASSWORD));

            assertThat(ConvertionUtils.arrayToAsciiString(plainText), equalTo(TEST_PLAIN_TEXT));
        }
    }
}

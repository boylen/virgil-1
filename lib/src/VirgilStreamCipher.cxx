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

#include <virgil/service/stream/VirgilStreamCipher.h>
using virgil::service::stream::VirgilStreamCipher;

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <virgil/crypto/VirgilKDF.h>
using virgil::crypto::VirgilKDF;

#include <virgil/crypto/VirgilSymmetricCipher.h>
using virgil::crypto::VirgilSymmetricCipher;

#include <virgil/crypto/VirgilAsymmetricCipher.h>
using virgil::crypto::VirgilAsymmetricCipher;


VirgilStreamCipher::~VirgilStreamCipher() throw() {
}

void VirgilStreamCipher::encrypt(VirgilDataSource& source, VirgilDataSink& sink) {

    VirgilSymmetricCipher& symmetricCipher = initEncryption();

    while (source.hasData() && sink.isGood()) {
        sink.write(symmetricCipher.update(source.read()));
    }
    if (sink.isGood()) {
        sink.write(symmetricCipher.finish());
    }

    buildContentInfo();
    clearCipherInfo();
}

void VirgilStreamCipher::decryptWithKey(VirgilDataSource& source, VirgilDataSink& sink,
        const VirgilByteArray& certificateId, const VirgilByteArray& privateKey,
        const VirgilByteArray& privateKeyPassword) {

    VirgilSymmetricCipher& symmetricCipher = initDecryptionWithKey(certificateId, privateKey, privateKeyPassword);

    while (source.hasData() && sink.isGood()) {
        sink.write(symmetricCipher.update(source.read()));
    }
    if (sink.isGood()) {
        sink.write(symmetricCipher.finish());
    }

    clearCipherInfo();
}

void VirgilStreamCipher::decryptWithPassword(VirgilDataSource& source, VirgilDataSink& sink,
        const VirgilByteArray& pwd) {
    VirgilSymmetricCipher& symmetricCipher = initDecryptionWithPassword(pwd);

    while (source.hasData() && sink.isGood()) {
        sink.write(symmetricCipher.update(source.read()));
    }
    if (sink.isGood()) {
        sink.write(symmetricCipher.finish());
    }

    clearCipherInfo();
}

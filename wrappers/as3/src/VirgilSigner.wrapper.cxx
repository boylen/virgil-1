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

#include <virgil/service/VirgilSigner.h>
using virgil::service::VirgilSigner;

GEN_CONSTRUCTOR(VirgilSigner, com.virgilsecurity.wrapper)
GEN_DESTRUCTOR(VirgilSigner, com.virgilsecurity.wrapper)

__attribute__((
    annotate("as3import:flash.utils.ByteArray"),
    annotate("as3sig:public function _wrap_VirgilSigner_sign"
            "(asSelf, asData:ByteArray, asSignerCertificateId:ByteArray,"
            "asPrivateKey:ByteArray, asPrivateKeyPassword:ByteArray = null):int"),
    annotate("as3package:com.virgilsecurity.wrapper")
))
void _wrap_VirgilSigner_sign() {
WRAPPER_THROWABLE_SECTION_START
    VirgilSigner *cSelf = (VirgilSigner *)0;
    AS3_GetScalarFromVar(cSelf, asSelf);

    VirgilByteArray cData;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asData, cData);

    VirgilByteArray cSignerCertificateId;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asSignerCertificateId, cSignerCertificateId);

    VirgilByteArray cPrivateKey;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asPrivateKey, cPrivateKey);

    bool cPasswordDefined = false;
    AS3_VAR_IS_DEFINED(asPrivateKeyPassword, cPasswordDefined);

    VirgilByteArray cPrivateKeyPassword;
    if (cPasswordDefined) {
        AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asPrivateKeyPassword, cPrivateKeyPassword);
    }

    VirgilSign *cSign = new VirgilSign(
            cSelf->sign(cData, cSignerCertificateId, cPrivateKey, cPrivateKeyPassword));

    AS3_DeclareVar(asSign, int);
    AS3_CopyScalarToVar(asSign, cSign);
    AS3_ReturnAS3Var(asSign);
WRAPPER_THROWABLE_SECTION_END
}

__attribute__((
    annotate("as3import:flash.utils.ByteArray"),
    annotate("as3sig:public function _wrap_VirgilSigner_verify"
            "(asSelf, asData:ByteArray, asSign:int, asPublicKey:ByteArray):Boolean"),
    annotate("as3package:com.virgilsecurity.wrapper")
))
void _wrap_VirgilSigner_verify() {
WRAPPER_THROWABLE_SECTION_START
    VirgilSigner *cSelf = (VirgilSigner *)0;
    AS3_GetScalarFromVar(cSelf, asSelf);

    VirgilByteArray cData;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asData, cData);

    VirgilSign *cSign = (VirgilSign *)0;
    AS3_GetScalarFromVar(cSign, asSign);

    VirgilByteArray cPublicKey;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asPublicKey, cPublicKey);

    bool cVerified = cSelf->verify(cData, *cSign, cPublicKey);

    AS3_DeclareVar(asVerified, Boolean);
    AS3_CopyScalarToVar(asVerified, cVerified);
    AS3_ReturnAS3Var(asVerified);
WRAPPER_THROWABLE_SECTION_END
}

__attribute__((
    annotate("as3import:flash.utils.ByteArray"),
    annotate("as3sig:public function _wrap_VirgilSigner_signTicket"
            "(asSelf, asTicket:int, asSignerCertificateId:ByteArray,"
            "asPrivateKey:ByteArray, asPrivateKeyPassword:ByteArray = null):int"),
    annotate("as3package:com.virgilsecurity.wrapper")
))
void _wrap_VirgilSigner_signTicket() {
WRAPPER_THROWABLE_SECTION_START
    VirgilSigner *cSelf = (VirgilSigner *)0;
    AS3_GetScalarFromVar(cSelf, asSelf);

    VirgilTicket *cTicket = (VirgilTicket *)0;
    AS3_GetScalarFromVar(cTicket, asTicket);

    VirgilByteArray cSignerCertificateId;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asSignerCertificateId, cSignerCertificateId);

    VirgilByteArray cPrivateKey;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asPrivateKey, cPrivateKey);

    bool cPasswordDefined = false;
    AS3_VAR_IS_DEFINED(asPrivateKeyPassword, cPasswordDefined);

    VirgilByteArray cPrivateKeyPassword;
    if (cPasswordDefined) {
        AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asPrivateKeyPassword, cPrivateKeyPassword);
    }

    VirgilSign *cSign = new VirgilSign(
            cSelf->sign(*cTicket, cSignerCertificateId, cPrivateKey, cPrivateKeyPassword));

    AS3_DeclareVar(asSign, int);
    AS3_CopyScalarToVar(asSign, cSign);
    AS3_ReturnAS3Var(asSign);
WRAPPER_THROWABLE_SECTION_END
}

__attribute__((
    annotate("as3import:flash.utils.ByteArray"),
    annotate("as3sig:public function _wrap_VirgilSigner_verifyTicket"
            "(asSelf, asTicket:int, asSign:int, asPublicKey:ByteArray):Boolean"),
    annotate("as3package:com.virgilsecurity.wrapper")
))
void _wrap_VirgilSigner_verifyTicket() {
WRAPPER_THROWABLE_SECTION_START
    VirgilSigner *cSelf = (VirgilSigner *)0;
    AS3_GetScalarFromVar(cSelf, asSelf);

    VirgilTicket *cTicket = (VirgilTicket *)0;
    AS3_GetScalarFromVar(cTicket, asTicket);

    VirgilSign *cSign = (VirgilSign *)0;
    AS3_GetScalarFromVar(cSign, asSign);

    VirgilByteArray cPublicKey;
    AS3_BYTE_ARRAY_TO_VIRGIL_BYTE_ARRAY(asPublicKey, cPublicKey);

    bool cVerified = cSelf->verify(*cTicket, *cSign, cPublicKey);

    AS3_DeclareVar(asVerified, Boolean);
    AS3_CopyScalarToVar(asVerified, cVerified);
    AS3_ReturnAS3Var(asVerified);
WRAPPER_THROWABLE_SECTION_END
}

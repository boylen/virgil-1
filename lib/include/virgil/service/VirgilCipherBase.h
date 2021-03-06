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

#ifndef VIRGIL_SERVICE_VIRGIL_CIPHER_BASE_H
#define VIRGIL_SERVICE_VIRGIL_CIPHER_BASE_H

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <virgil/crypto/VirgilRandom.h>
using virgil::crypto::VirgilRandom;

#include <virgil/crypto/VirgilSymmetricCipher.h>
using virgil::crypto::VirgilSymmetricCipher;

#include <virgil/service/data/VirgilKeyPair.h>
using virgil::service::data::VirgilKeyPair;

#include <virgil/crypto/VirgilContentInfo.h>
using virgil::crypto::VirgilContentInfo;

#include <virgil/crypto/VirgilCustomParams.h>
using virgil::crypto::VirgilCustomParams;

#include <virgil/crypto/cms/VirgilCMSEnvelopedData.h>
using virgil::crypto::cms::VirgilCMSEnvelopedData;

#include <map>
#include <set>

namespace virgil { namespace service {

/**
 * @brief This class provides configuration methods to all Virgil*Cipher classes.
 */
class VirgilCipherBase {
public:
    /**
     * @brief Initialize randomization module used by encryption.
     */
    VirgilCipherBase();
    /**
     * @brief Dispose used resources.
     */
    virtual ~VirgilCipherBase() throw();
public:
    /**
     * @name Recipent management
     */
    ///@{
    /**
     * @brief Add recipient defined with certficate id and public key.
     */
    void addKeyRecipient(const VirgilByteArray& certificateId, const VirgilByteArray& publicKey);
    /**
     * @brief Remove recipient with given certificate id.
     * @note If recipient with given certificate id is absent - do nothing.
     */
    void removeKeyRecipient(const VirgilByteArray& certificateId);
    /**
     * @brief Add recipient defined with password.
     */
    void addPasswordRecipient(const VirgilByteArray& pwd);
    /**
     * @brief Remove recipient with given password.
     * @note If recipient with given password is absent - do nothing.
     */
    void removePasswordRecipient(const VirgilByteArray& pwd);
    /**
     * @brief Remove all recipients.
     */
    void removeAllRecipients();
    ///@}
    /**
     * @name Content Info Access / Management
     */
    ///@{
    /**
     * @brief Returns encrypted data info.
     */
    /**
     * @brief Get VirgilContentInfo object as ASN.1 structure.
     * @note Call this method after encryption process.
     */
    VirgilByteArray getContentInfo() const;
    /**
     * @brief Create VirgilContentInfo object from ASN.1 structure.
     * @note Call this method before decryption process.
     */
    void setContentInfo(const VirgilByteArray& contentInfo);
    /**
     * @brief Provide access to the object that handles custom parameters.
     * @note Use this method to add custom parameters to the content info object.
     * @note Use this method before encryption process.
     */
    VirgilCustomParams& customParameters();
    /**
     * @brief Provide readonly access to the object that handles custom parameters.
     * @note Use this method to read custom parameters from the content info object.
     */
    const VirgilCustomParams& customParameters() const;
    ///@}
protected:
    /**
     * @brief Configures symmetric cipher for encryption.
     * @return Configured cipher.
     * @note cipher's key randomly generated.
     * @note cipher's input vector is randomly generated.
     */
    VirgilSymmetricCipher& initEncryption();
    /**
     * @brief Configures symmetric cipher for encryption.
     */
    /**
     * @brief Configures symmetric cipher for decryption.
     * @param encryptedDataInfo - serialized encrypted data info.
     * @param certificateId - certificate id that corresponds to the user's private key.
     * @param privateKey - user's private key.
     * @param privateKeyPassword - user's private key password.
     * @return Configured cipher.
     */
    VirgilSymmetricCipher& initDecryption(const VirgilByteArray& encryptedDataInfo,
            const VirgilByteArray& certificateId, const VirgilByteArray& privateKey,
            const VirgilByteArray& privateKeyPassword = VirgilByteArray());
    /**
     * @brief Configures symmetric cipher for decryption based on the recipient's password.
     * @param pwd - recipient's password.
     * @return Configured cipher.
     */
    VirgilSymmetricCipher& initDecryptionWithPassword(const VirgilByteArray& pwd);
    /**
     * @brief Configures symmetric cipher for decryption based on the recipient's certificate id and private key.
     * @param certificateId - recipient's certificate id.
     * @param privateKey - recipient's private key.
     * @param privateKeyPassword - recipient's private key password.
     * @return Configured cipher.
     */
    VirgilSymmetricCipher& initDecryptionWithKey(const VirgilByteArray& certificateId,
            const VirgilByteArray& privateKey, const VirgilByteArray& privateKeyPassword);
    /**
     * @brief Return symmetric cipher configure by one of the methods:
     *     initEncryption(), initDecryptionWithPassword(), initDecryptionWithKey.
     */
    VirgilSymmetricCipher& getSymmetricCipher();
    /**
     * @brief Build VirgilContentInfo object.
     *
     * This method SHOULD be called after encryption process is finished.
     * @note This method SHOULD be called after encryption process is finished.
     */
    void buildContentInfo();
     /**
      * @brief Clear all information related to the cipher.
      *
      * Clear symmetric cipher and correspond internal states.
      * @note This method SHOULD be called after encryption or decryption process is finished.
      * @note You CAN not use symmetric cipher returned by the method @link getSymmetricCipher () @endlink,
      *     after this method call.
      */
    void clearCipherInfo();
private:
    typedef std::map<VirgilByteArray, VirgilByteArray> KeyRecipientsType; /**< certificate id -> public key */
    typedef std::set<VirgilByteArray> PasswordRecipientsType; /**< passwords */
private:
    VirgilRandom random_;
    VirgilSymmetricCipher symmetricCipher_;
    VirgilByteArray symmetricCipherKey_;
    VirgilContentInfo contentInfo_;
    VirgilCMSEnvelopedData envelopedData_;
    KeyRecipientsType keyRecipients_;
    PasswordRecipientsType passwordRecipients_;
};

}}

#endif /* VIRGIL_SERVICE_VIRGIL_CIPHER_BASE_H */

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

#ifndef VIRGIL_CRYPTO_SYMMETRIC_SIPHER_H
#define VIRGIL_CRYPTO_SYMMETRIC_SIPHER_H

#include <string>

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <virgil/crypto/asn1/VirgilAsn1Compatible.h>
using virgil::crypto::asn1::VirgilAsn1Compatible;

namespace virgil { namespace crypto {

/**
 * @name Forward declarations
 */
///@{
class VirgilSymmetricCipherImpl;
///@}

/**
 * @brief Provides symmetric ciphers algorithms.
 */
class VirgilSymmetricCipher : public VirgilAsn1Compatible {
public:
    /**
     * @name Additional types
     */
    ///@{
    typedef enum {
        VirgilSymmetricCipherPadding_PKCS7,
        VirgilSymmetricCipherPadding_OneAndZeros,
        VirgilSymmetricCipherPadding_ZerosAndLen,
        VirgilSymmetricCipherPadding_Zeros
    } VirgilSymmetricCipherPadding;
    ///@}

public:
    /**
     * @name Creation methods
     */
    ///@{
    /**
     * @brief Creates object that handles AES-256 encryption / decription algorithms.
     */
    static VirgilSymmetricCipher aes256();
    ///@}
    /**
     * @brief Create object with undefined algorithm.
     * @warning SHOULD be used in conjunction with VirgilAsn1Compatible interface,
     *     i.e. VirgilSymmetricCipher cipher = VirgilSymmetricCipher().fromAsn1(asn1);
     */
    VirgilSymmetricCipher();
    /**
     * @brief Polymorphic destructor.
     */
    virtual ~VirgilSymmetricCipher() throw();
    ///@}
    /**
     * @name Info
     */
    ///@{
    /**
     * @brief Returns the name of the given cipher, as a string.
     */
    std::string name() const;
    /**
     * @brief Returns the block size of the current cipher.
     * @return block size, in octets.
     */
    size_t blockSize() const;
    /**
     * @brief Returns the size of the cipher's IV in bytes.
     */
    size_t ivSize() const;
    /**
     * @brief Returns the key length of the cipher.
     * @return key length, in bits.
     */
    size_t keySize() const;
    /**
     * @brief Returns the key length of the cipher.
     * @return key length, in octets.
     */
    size_t keyLength() const;
    /**
     * @brief Returns true if cipher is in the encryption mode.
     */
    bool isEncryptionMode() const;
    /**
     * @brief Returns true if cipher is in the decryption mode.
     */
    bool isDecryptionMode() const;
    ///@}

    /**
     * @name Configuration
     */
    ///@{
    /**
     * @brief Configures encryption key.
     *
     * Configures cipher to be used in encryption mode with given key.
     * @warning Only one key CAN be set.
     */
    void setEncryptionKey(const VirgilByteArray& key);
    /**
     * @brief Configures decryption key.
     *
     * Configures cipher to be used in decryption mode with given key.
     * @warning Only one key CAN be set.
     */
    void setDecryptionKey(const VirgilByteArray& key);
    /**
     * @brief Defines padding mode.
     *
     * Default value is PKCS7.
     * @note This parameter is used only for cipher modes that use padding.
     */
    void setPadding(VirgilSymmetricCipherPadding padding);
    /**
     * @brief Configures the initialization vector.
     */
    void setIV(const VirgilByteArray& iv);
    /**
     * @brief Finish preparation before encryption / decryption.
     */
    void reset();
    /**
     * @brief Clear all configuration settings.
     * @note This method SHOULD be used if class instance was used for encryption
     *           and then will be used for decryption, and vice versa.
     */
    void clear();
    ///@}
    /**
     * @name Generic Encryption / Decryption
     */
    ///@{
    /**
     * @brief Generic all-in-one encryption / decryption.
     *
     * Encrypts or decrypts given data.
     * @param input - data to be encrypted / decrypted.
     * @param iv - initialization vector.
     * @return Encrypted or decrypted bytes (rely on the current mode).
     */
    VirgilByteArray crypt(const VirgilByteArray& input, const VirgilByteArray& iv);
    ///@}
    /**
     * @name Sequence Encryption / Decryption
     */
    ///@{
    /**
     * @brief Generic cipher update function.
     *
     * Encrypts or decrypts given data.
     * Writes as many block size'd blocks of data as possible to output.
     * Any data that cannot be written immediately will either be added to the next block,
     *     or flushed when finish is called.
     * @return Encrypted or decrypted bytes (rely on the current mode).
     */
    VirgilByteArray update(const VirgilByteArray& input);
    /**
     * @brief Cipher finalization method.
     *
     * If data still needs to be flushed from an incomplete block,
     *     data contained within it will be padded with the size of the last block,
     *     and will be returned.
     * @return Encrypted or decrypted bytes (rely on the current mode).
     */
    VirgilByteArray finish();
    ///@}
    /**
     * @name Copy constructor / assignment operator
     * @warning Copy constructor and assignment operator create copy of the object as it was created
     *          by on of the creation methods. All changes in the internal state,
     *          that was made after creation, are not copied!
     */
    ///@{
    VirgilSymmetricCipher(const VirgilSymmetricCipher& other);
    VirgilSymmetricCipher& operator=(const VirgilSymmetricCipher& rhs);
    ///@}
    /**
     * @name VirgilAsn1Compatible implementation
     */
    ///@{
    virtual VirgilByteArray toAsn1() const;
    virtual void fromAsn1(const VirgilByteArray& asn1);
    ///@}
private:
    /**
     * @brief Creates and initialize cipher with specified type.
     * @warning Constructor CAN NOT be used directly, use one of factory methods to create apropriate cipher.
     */
    explicit VirgilSymmetricCipher(int type);
    /**
     * @brief If internal state is not initialized with specific algorithm exception will be thrown.
     */
    void checkState() const;
private:
    VirgilSymmetricCipherImpl *impl_;
};

}}

#endif /* VIRGIL_CRYPTO_SYMMETRIC_SIPHER_H */

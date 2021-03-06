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

#ifndef VIRGIL_CRYPTO_VIRGIL_CUSTOM_PARAMS_H
#define VIRGIL_CRYPTO_VIRGIL_CUSTOM_PARAMS_H

#include <virgil/crypto/asn1/VirgilAsn1Compatible.h>
using virgil::crypto::asn1::VirgilAsn1Compatible;

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <map>
#include <string>

namespace virgil { namespace crypto {

/**
 * @brief Data object that represent ASN.1 structure: VirgilCustomParams.
 */
class VirgilCustomParams : public VirgilAsn1Compatible {
public:
    /**
     * @name VirgilAsn1Compatible implementation
     *
     * Marshalling format:
     *     VirgilCustomParams ::= SET SIZE (1..MAX) OF KeyValue
     *
     *     KeyValue ::= SEQUENCE {
     *         key Key,
     *         val Value
     *     }
     *
     *     Key ::= UTF8String
     *
     *     Value ::= CHOICE {
     *         int  [0] EXPLICIT INTEGER,
     *         str  [1] EXPLICIT UTF8String,
     *         data [2] EXPLICIT OCTET STRING
     *     }
     */
    ///@{
    virtual VirgilByteArray toAsn1() const;
    virtual void fromAsn1(const VirgilByteArray& asn1);
    ///@}
public:
    /**
     * @name Info
     */
    ///@{
    /**
     * @brief Define whether no one parameter is set.
     */
    bool empty() const;
    ///@}
    /**
     * @name Manage Parameters
     * @note Key duplication is allowed for different parameter types.
     */
    ///@{
    /**
     * @brief Set parameter with type: Integer
     */
    void setInteger(const VirgilByteArray& key, int value);
    /**
     * @brief Get parameter with type: Integer
     * @throw VirgilCryptoException if given key is absent.
     */
    int getInteger(const VirgilByteArray& key) const;
    /**
     * @brief Remove parameter with type: Integer
     * @note Do nothing if given key is absent.
     */
    void removeInteger(const VirgilByteArray& key);
    /**
     * @brief Set parameter with type: String
     */
    void setString(const VirgilByteArray& key, const VirgilByteArray& value);
    /**
     * @brief Get parameter with type: String
     * @throw VirgilCryptoException if given key is absent.
     */
    VirgilByteArray getString(const VirgilByteArray& key) const;
    /**
     * @brief Remove parameter with type: String
     * @note Do nothing if given key is absent.
     */
    void removeString(const VirgilByteArray& key);
    /**
     * @brief Set parameter with type: Data
     */
    void setData(const VirgilByteArray& key, const VirgilByteArray& value);
    /**
     * @brief Get parameter with type: Data
     * @throw VirgilCryptoException if given key is absent.
     */
    VirgilByteArray getData(const VirgilByteArray& key) const;
    /**
     * @brief Remove parameter with type: Data
     * @note Do nothing if given key is absent.
     */
    void removeData(const VirgilByteArray& key);
    ///@}
    /**
     * @brief Polymorphic destructor.
     */
    virtual ~VirgilCustomParams() throw();
private:
    std::map<VirgilByteArray, int> intValues_;
    std::map<VirgilByteArray, VirgilByteArray> stringValues_;
    std::map<VirgilByteArray, VirgilByteArray> dataValues_;
};

}}

#endif /* VIRGIL_CRYPTO_VIRGIL_CUSTOM_PARAMS_H */

﻿/*
	bumo is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	bumo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with bumo.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BUBI_ACCOUNT_H_
#define BUBI_ACCOUNT_H_

#include <utils/base_int.h>
#include <utils/crypto.h>
#include <utils/logger.h>
#include <proto/cpp/chain.pb.h>
#include <utils/entry_cache.h>
#include "proto/cpp/merkeltrie.pb.h"
#include <common/storage.h>
#include "kv_trie.h"
namespace bumo {

	struct AssetSort {
		bool operator() (const protocol::AssetProperty& a, const protocol::AssetProperty& b)const{
			return a.SerializeAsString() < b.SerializeAsString();
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	struct StringSort {
		bool operator() (const std::string &l, const std::string &r) const {
			return l < r;
		}
	};


	class AccountFrm {
	public:

		typedef std::shared_ptr<AccountFrm>	pointer;

		//AccountFrm();
		AccountFrm(protocol::Account account);
		AccountFrm(std::shared_ptr< AccountFrm> account);

		~AccountFrm();

		void ToJson(Json::Value &result);

		void GetAllAssets(std::vector<protocol::Asset>& assets);

		void GetAllMetaData(std::vector<protocol::KeyPair>& metadata);

		std::string	Serializer();
		bool	UnSerializer(const std::string &str);

		std::string GetAccountAddress()const;

		bool GetAsset(const protocol::AssetProperty &_property, protocol::Asset& result);

		void SetAsset(const protocol::Asset& result);

		bool GetMetaData(const std::string& binkey, protocol::KeyPair& result);

		void SetMetaData(const protocol::KeyPair& result);

		bool DeleteMetaData(const protocol::KeyPair& dataptr);

		protocol::Account &GetProtoAccount() {
			return account_info_;
		}

		protocol::Account ProtocolAccount() const{
			return account_info_;
		}

		int64_t GetAccountNonce() const {
			return account_info_.nonce();
		}

		const int64_t GetProtoMasterWeight() const {
			return account_info_.priv().master_weight();
		}

		const int64_t GetProtoTxThreshold() const {
			return account_info_.priv().thresholds().tx_threshold();
		}

		const int64_t GetTypeThreshold(const protocol::Operation::Type type) const;

		void SetProtoMasterWeight(int64_t weight) {
			return account_info_.mutable_priv()->set_master_weight(weight);
		}

		void SetProtoTxThreshold(int64_t threshold) {
			return account_info_.mutable_priv()->mutable_thresholds()->set_tx_threshold(threshold);
		}

		bool UpdateSigner(const std::string &signer, int64_t weight);
		bool UpdateTypeThreshold(const protocol::Operation::Type type, int64_t threshold);
		void UpdateHash(std::shared_ptr<WRITE_BATCH> batch);
		void NonceIncrease();
		int64_t GetAccountBalance() const;
		bool AddBalance(int64_t amount);
	public:

		template <class T>
		struct DataCache{
			utils::ChangeAction action_;
			T data_;
		};

		std::map<protocol::AssetProperty, DataCache<protocol::Asset>, AssetSort> assets_;
		std::map<std::string, DataCache<protocol::KeyPair>> metadata_;
	private:
		protocol::Account	account_info_;
	};

}

#endif

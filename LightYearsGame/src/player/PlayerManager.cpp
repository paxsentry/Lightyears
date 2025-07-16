#include "player/PlayerManager.h"

namespace ly
{
    unique<PlayerManager> PlayerManager::mPlayerManager{ nullptr };

    PlayerManager::PlayerManager()
    {}

    PlayerManager& PlayerManager::Get()
    {
        if (!mPlayerManager)
        {
            mPlayerManager = std::move(unique<PlayerManager>{new PlayerManager{}});
        }

        return *mPlayerManager;
    }

    Player& PlayerManager::CreateNewPlayer()
    {
        mPlayers.emplace(mPlayers.begin(), Player());

        return mPlayers.back();
    }

    Player* PlayerManager::GetPlayer(int playerIndex)
    {
        if (playerIndex >= 0 && playerIndex < mPlayers.size())
        {
            return &(mPlayers[playerIndex]);
        }

        return nullptr;
    }

    const Player* PlayerManager::GetPlayer(int playerIndex) const
    {
        if (playerIndex >= 0 && playerIndex < mPlayers.size())
        {
            return &(mPlayers[playerIndex]);
        }

        return nullptr;
    }

    void PlayerManager::Reset()
    {
        mPlayers.clear();
    }
}
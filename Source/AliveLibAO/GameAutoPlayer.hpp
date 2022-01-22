#pragma once

#include "BaseGameAutoPlayer.hpp"

namespace AO {

class Recorder final : public BaseRecorder
{
public:
    void SaveObjectStates() override;
    void SaveRng(s32 rng);
};

class Player final : public BasePlayer
{
public:
    void ValidateObjectStates() override;
    s32 ReadRng();

private:
    void ValidateObject(s32 idx, bool logTypes);
};

class [[nodiscard]] GameAutoPlayer final : public BaseGameAutoPlayer
{
public:
    GameAutoPlayer()
        : BaseGameAutoPlayer(mAORecorder, mAOPlayer)
    {

    }

    s32 Rng(s32 rng);

private:
    u32 ReadInput(u32 padIdx) override;

    Recorder mAORecorder;
    Player mAOPlayer;
};

extern GameAutoPlayer gGameAutoPlayer;

} // namespace AO

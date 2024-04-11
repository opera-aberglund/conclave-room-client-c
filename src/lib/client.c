#include <conclave-room-client/client.h>

void clvRoomClientInit(ClvRoomClient* self, Clog log)
{
    self->log = log;
    self->leader = 0xff;
    self->term = 0xffff;
}

ClvRoomClientPingResult clvRoomClientOnPing(
    ClvRoomClient* self, ClvSerializePingResponse pingResponse)
{
    ClvRoomClientPingResult result = ClvRoomClientPingResultNothing;

    if (pingResponse.term == self->term) {
        return result;
    }

    if (self->term == 0) {
        CLOG_C_INFO(&self->log, "first time term: %d", pingResponse.term)
    } else {
        CLOG_C_INFO(&self->log, "new term detected: %d", pingResponse.term)
    }

    if (pingResponse.roomInfo.indexOfOwner != self->leader) {
        if (self->leader == 0xff) {
            CLOG_C_INFO(&self->log, "first time leader is %d", pingResponse.roomInfo.indexOfOwner)
        } else {
            CLOG_C_INFO(&self->log, "leader changed to %d", pingResponse.roomInfo.indexOfOwner)
        }
        result = ClvRoomClientPingResultLeaderChanged;
    } else {
        CLOG_C_INFO(
            &self->log, "but term changed, but leader is not changed (should rarely/ever happen)")
        result = ClvRoomClientPingResultSameLeaderButTermChanged;
    }

    self->leader = pingResponse.roomInfo.indexOfOwner;
    self->term = pingResponse.term;

    return result;
}

ClvSerializePing clvRoomClientPing(ClvRoomClient* self, ClvSerializeKnowledge knowledge,
    ClvSerializeConnectedToOwnerState connectionToLeader)
{
    //CLOG_C_INFO(&self->log, "ping %d", self->leader)
    self->lastConnectionStateToLeader = connectionToLeader;
    self->lastKnowledge = knowledge;

    ClvSerializePing ping = {
        .term = self->term,
        .connectedToOwner = connectionToLeader,
        .knowledge = knowledge,
    };

    return ping;
}

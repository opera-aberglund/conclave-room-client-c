#include <conclave-room-client/client.h>

void clvRoomClientInit(ClvRoomClient* self, Clog log)
{
    self->log = log;
    self->leader = 0xff;
}

void clvRoomClientOnPing(ClvRoomClient* self, ClvSerializePingResponse pingResponse)
{
    self->leader = pingResponse.roomInfo.indexOfOwner;
    if (pingResponse.term != self->term) {
        CLOG_C_INFO(& "new term detected: %d", pingResponse.term);
    }
    self->term = pingResponse.term;
}

ClvSerializePing clvRoomClientPing(ClvRoomClient* self, ClvSerializeKnowledge knowledge, ClvSerializeConnectedToOwnerState connectionToLeader)
{
    CLOG_C_INFO(& "ping %d", self->leader);
    self->lastConnectionStateToLeader = connectionToLeader;
    self->lastKnowledge = knowledge;

    ClvSerializePing ping = {
        .term = self->term,
        .connectedToOwner = connectionToLeader,
        .knowledge = knowledge,
    };

    return ping;
}

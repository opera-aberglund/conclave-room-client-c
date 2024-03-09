#ifndef CONCLAVE_ROOM_CLIENT_H
#define CONCLAVE_ROOM_CLIENT_H

#include <conclave-room-serialize/types.h>

#include <clog/clog.h>
#include <stdbool.h>

typedef struct ClvRoomClient {
    Clog log;
    uint8_t leader;
    ClvSerializeTerm term;

    ClvSerializeKnowledge lastKnowledge;
    ClvSerializeConnectedToOwnerState lastConnectionStateToLeader;
} ClvRoomClient;

typedef enum ClvRoomClientPingResult {
    ClvRoomClientPingResultNothing,
    ClvRoomClientPingResultLeaderChanged,
    ClvRoomClientPingResultSameLeaderButTermChanged
} ClvRoomClientPingResult;

void clvRoomClientInit(ClvRoomClient* self, Clog log);
ClvRoomClientPingResult clvRoomClientOnPing(
    ClvRoomClient* self, ClvSerializePingResponse pingResponse);
ClvSerializePing clvRoomClientPing(ClvRoomClient* self, ClvSerializeKnowledge knowledge,
    ClvSerializeConnectedToOwnerState leaderConnectionState);

#endif

#ifndef CONCLAVE_ROOM_CLIENT_SERIALIZE_H
#define CONCLAVE_ROOM_CLIENT_SERIALIZE_H

#include <conclave-room-serialize/serialize.h>
#include <conclave-room-client/client.h>

#include <clog/clog.h>
#include <stdbool.h>

struct FldInStream;
struct FldOutStream;

typedef struct ClvRoomClientSerialize {
    Clog log;
    ClvRoomClient state;
} ClvRoomClientSerialize;

void clvSerializeRoomClientInit(ClvRoomClientSerialize* self, Clog log);
void clvSerializeRoomClientOnPing(ClvRoomClientSerialize* self, struct FldInStream* inStream);
void clvSerializeRoomClientSendPing(ClvRoomClientSerialize* self, ClvSerializeKnowledge knowledge, ClvSerializeConnectedToOwnerState leaderConnectionState, struct FldOutStream* outStream);

#endif

#include <conclave-room-client/client_serialize.h>
#include <conclave-room-client/client.h>
#include <conclave-room-serialize/client_in.h>
#include <conclave-room-serialize/client_out.h>

void clvSerializeRoomClientInit(ClvRoomClientSerialize* self, Clog log)
{
    clvRoomClientInit(&self->state, log);
}

void clvSerializeRoomClientOnPing(ClvRoomClientSerialize* self, struct FldInStream* inStream)
{
    ClvSerializePingResponse pingResponse;

    clvRoomSerializeClientInPingResponse(inStream, &pingResponse);

    clvRoomClientOnPing(&self->state, pingResponse);
}

void clvSerializeRoomClientSendPing(ClvRoomClientSerialize* self, ClvSerializeKnowledge knowledge,
    ClvSerializeConnectedToOwnerState leaderConnectionState, struct FldOutStream* outStream)
{
    ClvSerializePing ping = clvRoomClientPing(&self->state, knowledge, leaderConnectionState);
    clvRoomSerializeClientOutPing(outStream, &ping);
}

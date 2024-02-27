#include <conclave-room-client/client.h>
#include <conclave-room-client/client_serialize.h>
#include <conclave-room-serialize/client_in.h>
#include <conclave-room-serialize/client_out.h>
#include <flood/in_stream.h>

void clvSerializeRoomClientInit(ClvRoomClientSerialize* self, Clog log)
{
    clvRoomClientInit(&self->state, log);
}

ClvRoomClientPingResult clvSerializeRoomClientOnPing(
    ClvRoomClientSerialize* self, struct FldInStream* inStream)
{
    ClvSerializePingResponse pingResponse;

    clvRoomSerializeClientInPingResponse(inStream, &pingResponse);

    return clvRoomClientOnPing(&self->state, pingResponse);
}

void clvSerializeRoomClientSendPing(ClvRoomClientSerialize* self, ClvSerializeKnowledge knowledge,
    ClvSerializeConnectedToOwnerState leaderConnectionState, struct FldOutStream* outStream)
{
    ClvSerializePing ping = clvRoomClientPing(&self->state, knowledge, leaderConnectionState);
    clvRoomSerializeClientOutPing(outStream, &ping);
}

int clvSerializeRoomClientRead(ClvRoomClientSerialize* self, struct FldInStream* inStream)
{
    uint8_t cmd;
    fldInStreamReadUInt8(inStream, &cmd);

    switch (cmd) {
    case clvRoomSerializeCmdPing:
        clvSerializeRoomClientOnPing(self, inStream);
        return 0;
    default:
        return -4;
    }
}

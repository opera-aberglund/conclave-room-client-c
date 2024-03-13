#include <conclave-room-client/client.h>
#include <conclave-room-client/client_serialize.h>
#include <conclave-room-serialize/client_in.h>
#include <conclave-room-serialize/client_out.h>
#include <flood/in_stream.h>

void clvSerializeRoomClientInit(ClvRoomClientSerialize* self, Clog log)
{
    clvRoomClientInit(&self->state, log);
}

int clvSerializeRoomClientOnPing(
    ClvRoomClientSerialize* self, struct FldInStream* inStream, ClvRoomClientPingResult* result)
{
    ClvSerializePingResponse pingResponse;

    int error = clvRoomSerializeClientInPingResponse(inStream, &pingResponse);
    if (error != 0) {
        return error;
    }

    *result = clvRoomClientOnPing(&self->state, pingResponse);

    return 0;
}

int clvSerializeRoomClientSendPing(ClvRoomClientSerialize* self, ClvSerializeKnowledge knowledge,
    ClvSerializeConnectedToOwnerState leaderConnectionState, struct FldOutStream* outStream)
{
    ClvSerializePing ping = clvRoomClientPing(&self->state, knowledge, leaderConnectionState);
    return clvRoomSerializeClientOutPing(outStream, &ping);
}

int clvSerializeRoomClientRead(
    ClvRoomClientSerialize* self, struct FldInStream* inStream, ClvRoomClientReadResult* result)
{
    uint8_t cmd;
    int error = fldInStreamReadUInt8(inStream, &cmd);
    if (error != 0) {
        result->type = ClvRoomClientReadResultTypeError;
        return error;
    }

    switch (cmd) {
    case clvRoomSerializeCmdPingResponse:
        error = clvSerializeRoomClientOnPing(self, inStream, &result->pingResult);
        if (error != 0) {
            result->type = ClvRoomClientReadResultTypeError;
            return error;
        }
        result->type = ClvRoomClientReadResultTypePing;
        return 0;
    default:
        result->type = ClvRoomClientReadResultTypeError;
        return -4;
    }
}

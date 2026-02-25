#pragma once

#include "pas2c.h"

#include "SDLh.h"
void uchat_initModule();
void uchat_freeModule();
void uchat_ReloadLines();
void uchat_CleanupInput();
void uchat_CloseChat();
void uchat_RestoreChat();
void uchat_AddChatString(string255 s);
void uchat_DrawChat();
void uchat_KeyPressChat(TSDL_Keysym keysym);
void uchat_SendHogSpeech(string255 s);
void uchat_CopyToClipboard(string255 (*newContent));
void uchat_TextInput(TSDL_TextInputEvent (*event));


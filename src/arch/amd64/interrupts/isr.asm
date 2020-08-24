extern _c_isr_handlers

%macro  isr_err 1
    push qword %1

    ; Push all registers
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

%if %1 >= 32 && %1 < 40
    mov al, 0x20
    out 0x20, al
%elif %1 >= 40 && %1 < 48
    mov al, 0x20
    out 0x20, al
    out 0xA0, al
%endif

    mov rax, %1*8
    jmp _isr_common
%endmacro

%macro  isr_no_err 1
    push qword 0
    push qword %1

    ; Push all registers
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

%if %1 >= 32 && %1 < 40
    mov al, 0x20
    out 0x20, al
%elif %1 >= 40 && %1 < 48
    mov al, 0x20
    out 0x20, al
    out 0xA0, al
%endif

    mov rax, %1*8
    jmp _isr_common
%endmacro

_isr_common:
    mov rbx, cr0
    push rbx
    mov rbx, cr2
    push rbx
    mov rbx, cr3
    push rbx
    mov rbx, cr4
    push rbx

    mov rdi, rsp
    mov rbx, [_c_isr_handlers + rax]
    call rbx

    pop rbx
    mov cr4, rbx
    pop rbx
    mov cr3, rbx
    pop rbx
    mov cr2, rbx
    pop rbx
    mov cr0, rbx

    ; Pop all registers
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; Pop int no and error code
    add esp, 16

    iretq

; Define all ISRs
global _isr0
global _isr1
global _isr2
global _isr3
global _isr4
global _isr5
global _isr6
global _isr7
global _isr8
global _isr9
global _isr10
global _isr11
global _isr12
global _isr13
global _isr14
global _isr15
global _isr16
global _isr17
global _isr18
global _isr19
global _isr20
global _isr21
global _isr22
global _isr23
global _isr24
global _isr25
global _isr26
global _isr27
global _isr28
global _isr29
global _isr30
global _isr31
global _isr32
global _isr33
global _isr34
global _isr35
global _isr36
global _isr37
global _isr38
global _isr39
global _isr40
global _isr41
global _isr42
global _isr43
global _isr44
global _isr45
global _isr46
global _isr47
global _isr48
global _isr49
global _isr50
global _isr51
global _isr52
global _isr53
global _isr54
global _isr55
global _isr56
global _isr57
global _isr58
global _isr59
global _isr60
global _isr61
global _isr62
global _isr63
global _isr64
global _isr65
global _isr66
global _isr67
global _isr68
global _isr69
global _isr70
global _isr71
global _isr72
global _isr73
global _isr74
global _isr75
global _isr76
global _isr77
global _isr78
global _isr79
global _isr80
global _isr81
global _isr82
global _isr83
global _isr84
global _isr85
global _isr86
global _isr87
global _isr88
global _isr89
global _isr90
global _isr91
global _isr92
global _isr93
global _isr94
global _isr95
global _isr96
global _isr97
global _isr98
global _isr99
global _isr100
global _isr101
global _isr102
global _isr103
global _isr104
global _isr105
global _isr106
global _isr107
global _isr108
global _isr109
global _isr110
global _isr111
global _isr112
global _isr113
global _isr114
global _isr115
global _isr116
global _isr117
global _isr118
global _isr119
global _isr120
global _isr121
global _isr122
global _isr123
global _isr124
global _isr125
global _isr126
global _isr127
global _isr128
global _isr129
global _isr130
global _isr131
global _isr132
global _isr133
global _isr134
global _isr135
global _isr136
global _isr137
global _isr138
global _isr139
global _isr140
global _isr141
global _isr142
global _isr143
global _isr144
global _isr145
global _isr146
global _isr147
global _isr148
global _isr149
global _isr150
global _isr151
global _isr152
global _isr153
global _isr154
global _isr155
global _isr156
global _isr157
global _isr158
global _isr159
global _isr160
global _isr161
global _isr162
global _isr163
global _isr164
global _isr165
global _isr166
global _isr167
global _isr168
global _isr169
global _isr170
global _isr171
global _isr172
global _isr173
global _isr174
global _isr175
global _isr176
global _isr177
global _isr178
global _isr179
global _isr180
global _isr181
global _isr182
global _isr183
global _isr184
global _isr185
global _isr186
global _isr187
global _isr188
global _isr189
global _isr190
global _isr191
global _isr192
global _isr193
global _isr194
global _isr195
global _isr196
global _isr197
global _isr198
global _isr199
global _isr200
global _isr201
global _isr202
global _isr203
global _isr204
global _isr205
global _isr206
global _isr207
global _isr208
global _isr209
global _isr210
global _isr211
global _isr212
global _isr213
global _isr214
global _isr215
global _isr216
global _isr217
global _isr218
global _isr219
global _isr220
global _isr221
global _isr222
global _isr223
global _isr224
global _isr225
global _isr226
global _isr227
global _isr228
global _isr229
global _isr230
global _isr231
global _isr232
global _isr233
global _isr234
global _isr235
global _isr236
global _isr237
global _isr238
global _isr239
global _isr240
global _isr241
global _isr242
global _isr243
global _isr244
global _isr245
global _isr246
global _isr247
global _isr248
global _isr249
global _isr250
global _isr251
global _isr252
global _isr253
global _isr254
global _isr255

_isr0: isr_no_err 0
_isr1: isr_no_err 1
_isr2: isr_no_err 2
_isr3: isr_no_err 3
_isr4: isr_no_err 4
_isr5: isr_no_err 5
_isr6: isr_no_err 6
_isr7: isr_no_err 7
_isr8: isr_err 8
_isr9: isr_no_err 9
_isr10: isr_err 10
_isr11: isr_err 11
_isr12: isr_err 12
_isr13: isr_err 13
_isr14: isr_err 14
_isr15: isr_no_err 15
_isr16: isr_no_err 16
_isr17: isr_err 17
_isr18: isr_no_err 18
_isr19: isr_no_err 19
_isr20: isr_no_err 20
_isr21: isr_no_err 21
_isr22: isr_no_err 22
_isr23: isr_no_err 23
_isr24: isr_no_err 24
_isr25: isr_no_err 25
_isr26: isr_no_err 26
_isr27: isr_no_err 27
_isr28: isr_no_err 28
_isr29: isr_no_err 29
_isr30: isr_no_err 30
_isr31: isr_no_err 31
_isr32: isr_no_err 32
_isr33: isr_no_err 33
_isr34: isr_no_err 34
_isr35: isr_no_err 35
_isr36: isr_no_err 36
_isr37: isr_no_err 37
_isr38: isr_no_err 38
_isr39: isr_no_err 39
_isr40: isr_no_err 40
_isr41: isr_no_err 41
_isr42: isr_no_err 42
_isr43: isr_no_err 43
_isr44: isr_no_err 44
_isr45: isr_no_err 45
_isr46: isr_no_err 46
_isr47: isr_no_err 47
_isr48: isr_no_err 48
_isr49: isr_no_err 49
_isr50: isr_no_err 50
_isr51: isr_no_err 51
_isr52: isr_no_err 52
_isr53: isr_no_err 53
_isr54: isr_no_err 54
_isr55: isr_no_err 55
_isr56: isr_no_err 56
_isr57: isr_no_err 57
_isr58: isr_no_err 58
_isr59: isr_no_err 59
_isr60: isr_no_err 60
_isr61: isr_no_err 61
_isr62: isr_no_err 62
_isr63: isr_no_err 63
_isr64: isr_no_err 64
_isr65: isr_no_err 65
_isr66: isr_no_err 66
_isr67: isr_no_err 67
_isr68: isr_no_err 68
_isr69: isr_no_err 69
_isr70: isr_no_err 70
_isr71: isr_no_err 71
_isr72: isr_no_err 72
_isr73: isr_no_err 73
_isr74: isr_no_err 74
_isr75: isr_no_err 75
_isr76: isr_no_err 76
_isr77: isr_no_err 77
_isr78: isr_no_err 78
_isr79: isr_no_err 79
_isr80: isr_no_err 80
_isr81: isr_no_err 81
_isr82: isr_no_err 82
_isr83: isr_no_err 83
_isr84: isr_no_err 84
_isr85: isr_no_err 85
_isr86: isr_no_err 86
_isr87: isr_no_err 87
_isr88: isr_no_err 88
_isr89: isr_no_err 89
_isr90: isr_no_err 90
_isr91: isr_no_err 91
_isr92: isr_no_err 92
_isr93: isr_no_err 93
_isr94: isr_no_err 94
_isr95: isr_no_err 95
_isr96: isr_no_err 96
_isr97: isr_no_err 97
_isr98: isr_no_err 98
_isr99: isr_no_err 99
_isr100: isr_no_err 100
_isr101: isr_no_err 101
_isr102: isr_no_err 102
_isr103: isr_no_err 103
_isr104: isr_no_err 104
_isr105: isr_no_err 105
_isr106: isr_no_err 106
_isr107: isr_no_err 107
_isr108: isr_no_err 108
_isr109: isr_no_err 109
_isr110: isr_no_err 110
_isr111: isr_no_err 111
_isr112: isr_no_err 112
_isr113: isr_no_err 113
_isr114: isr_no_err 114
_isr115: isr_no_err 115
_isr116: isr_no_err 116
_isr117: isr_no_err 117
_isr118: isr_no_err 118
_isr119: isr_no_err 119
_isr120: isr_no_err 120
_isr121: isr_no_err 121
_isr122: isr_no_err 122
_isr123: isr_no_err 123
_isr124: isr_no_err 124
_isr125: isr_no_err 125
_isr126: isr_no_err 126
_isr127: isr_no_err 127
_isr128: isr_no_err 128
_isr129: isr_no_err 129
_isr130: isr_no_err 130
_isr131: isr_no_err 131
_isr132: isr_no_err 132
_isr133: isr_no_err 133
_isr134: isr_no_err 134
_isr135: isr_no_err 135
_isr136: isr_no_err 136
_isr137: isr_no_err 137
_isr138: isr_no_err 138
_isr139: isr_no_err 139
_isr140: isr_no_err 140
_isr141: isr_no_err 141
_isr142: isr_no_err 142
_isr143: isr_no_err 143
_isr144: isr_no_err 144
_isr145: isr_no_err 145
_isr146: isr_no_err 146
_isr147: isr_no_err 147
_isr148: isr_no_err 148
_isr149: isr_no_err 149
_isr150: isr_no_err 150
_isr151: isr_no_err 151
_isr152: isr_no_err 152
_isr153: isr_no_err 153
_isr154: isr_no_err 154
_isr155: isr_no_err 155
_isr156: isr_no_err 156
_isr157: isr_no_err 157
_isr158: isr_no_err 158
_isr159: isr_no_err 159
_isr160: isr_no_err 160
_isr161: isr_no_err 161
_isr162: isr_no_err 162
_isr163: isr_no_err 163
_isr164: isr_no_err 164
_isr165: isr_no_err 165
_isr166: isr_no_err 166
_isr167: isr_no_err 167
_isr168: isr_no_err 168
_isr169: isr_no_err 169
_isr170: isr_no_err 170
_isr171: isr_no_err 171
_isr172: isr_no_err 172
_isr173: isr_no_err 173
_isr174: isr_no_err 174
_isr175: isr_no_err 175
_isr176: isr_no_err 176
_isr177: isr_no_err 177
_isr178: isr_no_err 178
_isr179: isr_no_err 179
_isr180: isr_no_err 180
_isr181: isr_no_err 181
_isr182: isr_no_err 182
_isr183: isr_no_err 183
_isr184: isr_no_err 184
_isr185: isr_no_err 185
_isr186: isr_no_err 186
_isr187: isr_no_err 187
_isr188: isr_no_err 188
_isr189: isr_no_err 189
_isr190: isr_no_err 190
_isr191: isr_no_err 191
_isr192: isr_no_err 192
_isr193: isr_no_err 193
_isr194: isr_no_err 194
_isr195: isr_no_err 195
_isr196: isr_no_err 196
_isr197: isr_no_err 197
_isr198: isr_no_err 198
_isr199: isr_no_err 199
_isr200: isr_no_err 200
_isr201: isr_no_err 201
_isr202: isr_no_err 202
_isr203: isr_no_err 203
_isr204: isr_no_err 204
_isr205: isr_no_err 205
_isr206: isr_no_err 206
_isr207: isr_no_err 207
_isr208: isr_no_err 208
_isr209: isr_no_err 209
_isr210: isr_no_err 210
_isr211: isr_no_err 211
_isr212: isr_no_err 212
_isr213: isr_no_err 213
_isr214: isr_no_err 214
_isr215: isr_no_err 215
_isr216: isr_no_err 216
_isr217: isr_no_err 217
_isr218: isr_no_err 218
_isr219: isr_no_err 219
_isr220: isr_no_err 220
_isr221: isr_no_err 221
_isr222: isr_no_err 222
_isr223: isr_no_err 223
_isr224: isr_no_err 224
_isr225: isr_no_err 225
_isr226: isr_no_err 226
_isr227: isr_no_err 227
_isr228: isr_no_err 228
_isr229: isr_no_err 229
_isr230: isr_no_err 230
_isr231: isr_no_err 231
_isr232: isr_no_err 232
_isr233: isr_no_err 233
_isr234: isr_no_err 234
_isr235: isr_no_err 235
_isr236: isr_no_err 236
_isr237: isr_no_err 237
_isr238: isr_no_err 238
_isr239: isr_no_err 239
_isr240: isr_no_err 240
_isr241: isr_no_err 241
_isr242: isr_no_err 242
_isr243: isr_no_err 243
_isr244: isr_no_err 244
_isr245: isr_no_err 245
_isr246: isr_no_err 246
_isr247: isr_no_err 247
_isr248: isr_no_err 248
_isr249: isr_no_err 249
_isr250: isr_no_err 250
_isr251: isr_no_err 251
_isr252: isr_no_err 252
_isr253: isr_no_err 253
_isr254: isr_no_err 254
_isr255: isr_no_err 255
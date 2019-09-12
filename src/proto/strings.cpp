#include "strings.hpp"

namespace proto {

std::optional<int32_t> encode(rune_t c) {
	switch (c) {
		case 0x000000:
			return 0;

		case 0x0000C0:
			return 1;

		case 0x0000C1:
			return 2;

		case 0x0000C2:
			return 3;

		case 0x0000C3:
			return 4;

		case 0x0000C4:
			return 5;

		case 0x0000C5:
			return 6;

		case 0x0000C6:
			return 7;

		case 0x0000C7:
			return 8;

		case 0x000009:
			return 9;

		case 0x00000A:
			return 10;

		case 0x00000B:
			return 11;

		case 0x00000D:
			return 13;

		case 0x0000C8:
			return 14;

		case 0x0000C9:
			return 15;

		case 0x0000CA:
			return 16;

		case 0x0000CB:
			return 17;

		case 0x0000CC:
			return 18;

		case 0x0000CD:
			return 19;

		case 0x0000CE:
			return 20;

		case 0x0000CF:
			return 21;

		case 0x0000D1:
			return 22;

		case 0x0000D2:
			return 23;

		case 0x0000D3:
			return 24;

		case 0x0000D4:
			return 25;

		case 0x0000D5:
			return 26;

		case 0x0000D6:
			return 27;

		case 0x0000D8:
			return 28;

		case 0x0000D9:
			return 29;

		case 0x0000DA:
			return 30;

		case 0x0000DB:
			return 31;

		case 0x000020:
			return 32;

		case 0x000021:
			return 33;

		case 0x000022:
			return 34;

		case 0x000023:
			return 35;

		case 0x000024:
			return 36;

		case 0x000025:
			return 37;

		case 0x000026:
			return 38;

		case 0x000027:
			return 39;

		case 0x000028:
			return 40;

		case 0x000029:
			return 41;

		case 0x00002A:
			return 42;

		case 0x00002B:
			return 43;

		case 0x00002C:
			return 44;

		case 0x00002D:
			return 45;

		case 0x00002E:
			return 46;

		case 0x00002F:
			return 47;

		case 0x000030:
			return 48;

		case 0x000031:
			return 49;

		case 0x000032:
			return 50;

		case 0x000033:
			return 51;

		case 0x000034:
			return 52;

		case 0x000035:
			return 53;

		case 0x000036:
			return 54;

		case 0x000037:
			return 55;

		case 0x000038:
			return 56;

		case 0x000039:
			return 57;

		case 0x00003A:
			return 58;

		case 0x00003B:
			return 59;

		case 0x00003C:
			return 60;

		case 0x00003D:
			return 61;

		case 0x00003E:
			return 62;

		case 0x00003F:
			return 63;

		case 0x000040:
			return 64;

		case 0x000041:
			return 65;

		case 0x000042:
			return 66;

		case 0x000043:
			return 67;

		case 0x000044:
			return 68;

		case 0x000045:
			return 69;

		case 0x000046:
			return 70;

		case 0x000047:
			return 71;

		case 0x000048:
			return 72;

		case 0x000049:
			return 73;

		case 0x00004A:
			return 74;

		case 0x00004B:
			return 75;

		case 0x00004C:
			return 76;

		case 0x00004D:
			return 77;

		case 0x00004E:
			return 78;

		case 0x00004F:
			return 79;

		case 0x000050:
			return 80;

		case 0x000051:
			return 81;

		case 0x000052:
			return 82;

		case 0x000053:
			return 83;

		case 0x000054:
			return 84;

		case 0x000055:
			return 85;

		case 0x000056:
			return 86;

		case 0x000057:
			return 87;

		case 0x000058:
			return 88;

		case 0x000059:
			return 89;

		case 0x00005A:
			return 90;

		case 0x00005B:
			return 91;

		case 0x00005C:
			return 92;

		case 0x00005D:
			return 93;

		case 0x00005E:
			return 94;

		case 0x00005F:
			return 95;

		case 0x000060:
			return 96;

		case 0x000061:
			return 97;

		case 0x000062:
			return 98;

		case 0x000063:
			return 99;

		case 0x000064:
			return 100;

		case 0x000065:
			return 101;

		case 0x000066:
			return 102;

		case 0x000067:
			return 103;

		case 0x000068:
			return 104;

		case 0x000069:
			return 105;

		case 0x00006A:
			return 106;

		case 0x00006B:
			return 107;

		case 0x00006C:
			return 108;

		case 0x00006D:
			return 109;

		case 0x00006E:
			return 110;

		case 0x00006F:
			return 111;

		case 0x000070:
			return 112;

		case 0x000071:
			return 113;

		case 0x000072:
			return 114;

		case 0x000073:
			return 115;

		case 0x000074:
			return 116;

		case 0x000075:
			return 117;

		case 0x000076:
			return 118;

		case 0x000077:
			return 119;

		case 0x000078:
			return 120;

		case 0x000079:
			return 121;

		case 0x00007A:
			return 122;

		case 0x00007B:
			return 123;

		case 0x00007C:
			return 124;

		case 0x00007D:
			return 125;

		case 0x00007E:
			return 126;

		case 0x0000DC:
			return 127;

		case 0x0000DD:
			return 128;

		case 0x0000DF:
			return 129;

		case 0x0000E0:
			return 130;

		case 0x0000E1:
			return 131;

		case 0x0000E2:
			return 132;

		case 0x0000E3:
			return 133;

		case 0x0000E4:
			return 134;

		case 0x0000E5:
			return 135;

		case 0x0000E6:
			return 136;

		case 0x0000E7:
			return 137;

		case 0x0000E8:
			return 138;

		case 0x0000E9:
			return 139;

		case 0x0000EA:
			return 140;

		case 0x0000EB:
			return 141;

		case 0x0000EC:
			return 142;

		case 0x0000ED:
			return 143;

		case 0x0000EE:
			return 144;

		case 0x0000EF:
			return 145;

		case 0x0000F1:
			return 146;

		case 0x0000F2:
			return 147;

		case 0x0000F3:
			return 148;

		case 0x0000F4:
			return 149;

		case 0x0000F5:
			return 150;

		case 0x0000F6:
			return 151;

		case 0x0000F8:
			return 152;

		case 0x0000F9:
			return 153;

		case 0x0000FA:
			return 154;

		case 0x0000FB:
			return 155;

		case 0x0000FC:
			return 156;

		case 0x0000FD:
			return 157;

		case 0x0000FF:
			return 158;

		case 0x000104:
			return 159;

		case 0x000105:
			return 160;

		case 0x000106:
			return 161;

		case 0x000107:
			return 162;

		case 0x00010C:
			return 163;

		case 0x00010D:
			return 164;

		case 0x00010E:
			return 165;

		case 0x00010F:
			return 166;

		case 0x000118:
			return 167;

		case 0x000119:
			return 168;

		case 0x00011A:
			return 169;

		case 0x00011B:
			return 170;

		case 0x00011E:
			return 171;

		case 0x00011F:
			return 172;

		case 0x000130:
			return 173;

		case 0x000131:
			return 174;

		case 0x000141:
			return 175;

		case 0x000142:
			return 176;

		case 0x000143:
			return 177;

		case 0x000144:
			return 178;

		case 0x000147:
			return 179;

		case 0x000148:
			return 180;

		case 0x000150:
			return 181;

		case 0x000151:
			return 182;

		case 0x000152:
			return 183;

		case 0x000153:
			return 184;

		case 0x000158:
			return 185;

		case 0x000159:
			return 186;

		case 0x00015A:
			return 187;

		case 0x00015B:
			return 188;

		case 0x00015E:
			return 189;

		case 0x00015F:
			return 190;

		case 0x000160:
			return 191;

		case 0x000161:
			return 192;

		case 0x000164:
			return 193;

		case 0x000165:
			return 194;

		case 0x00016E:
			return 195;

		case 0x00016F:
			return 196;

		case 0x000170:
			return 197;

		case 0x000171:
			return 198;

		case 0x000178:
			return 199;

		case 0x000179:
			return 200;

		case 0x00017A:
			return 201;

		case 0x00017B:
			return 202;

		case 0x00017C:
			return 203;

		case 0x00017D:
			return 204;

		case 0x00017E:
			return 205;

		case 0x000404:
			return 206;

		case 0x000411:
			return 207;

		case 0x000413:
			return 208;

		case 0x000414:
			return 209;

		case 0x000416:
			return 210;

		case 0x000417:
			return 211;

		case 0x000418:
			return 212;

		case 0x000419:
			return 213;

		case 0x00041B:
			return 214;

		case 0x00041F:
			return 215;

		case 0x000423:
			return 216;

		case 0x000424:
			return 217;

		case 0x000426:
			return 218;

		case 0x000427:
			return 219;

		case 0x000428:
			return 220;

		case 0x000429:
			return 221;

		case 0x00042A:
			return 222;

		case 0x00042B:
			return 223;

		case 0x00042C:
			return 224;

		case 0x00042D:
			return 225;

		case 0x00042E:
			return 226;

		case 0x00042F:
			return 227;

		case 0x000431:
			return 228;

		case 0x000432:
			return 229;

		case 0x000433:
			return 230;

		case 0x000434:
			return 231;

		case 0x000436:
			return 232;

		case 0x000437:
			return 233;

		case 0x000438:
			return 234;

		case 0x000439:
			return 235;

		case 0x00043A:
			return 236;

		case 0x00043B:
			return 237;

		case 0x00043C:
			return 238;

		case 0x00043D:
			return 239;

		case 0x00043F:
			return 240;

		case 0x000442:
			return 241;

		case 0x000444:
			return 242;

		case 0x000446:
			return 243;

		case 0x000447:
			return 244;

		case 0x000448:
			return 245;

		case 0x000449:
			return 246;

		case 0x00044A:
			return 247;

		case 0x00044B:
			return 248;

		case 0x00044C:
			return 249;

		case 0x00044D:
			return 250;

		case 0x00044E:
			return 251;

		case 0x00044F:
			return 252;

		case 0x000454:
			return 253;

		case 0x000490:
			return 254;

		case 0x000491:
			return 255;

		default:
			return {};
	}
}

std::optional<rune_t> decode(int32_t c) {
	switch (c) {
		case 0:
			return 0x000000;

		case 1:
			return 0x0000C0;

		case 2:
			return 0x0000C1;

		case 3:
			return 0x0000C2;

		case 4:
			return 0x0000C3;

		case 5:
			return 0x0000C4;

		case 6:
			return 0x0000C5;

		case 7:
			return 0x0000C6;

		case 8:
			return 0x0000C7;

		case 9:
			return 0x000009;

		case 10:
			return 0x00000A;

		case 11:
			return 0x00000B;

		case 12:
		case 13:
			return 0x00000D;

		case 14:
			return 0x0000C8;

		case 15:
			return 0x0000C9;

		case 16:
			return 0x0000CA;

		case 17:
			return 0x0000CB;

		case 18:
			return 0x0000CC;

		case 19:
			return 0x0000CD;

		case 20:
			return 0x0000CE;

		case 21:
			return 0x0000CF;

		case 22:
			return 0x0000D1;

		case 23:
			return 0x0000D2;

		case 24:
			return 0x0000D3;

		case 25:
			return 0x0000D4;

		case 26:
			return 0x0000D5;

		case 27:
			return 0x0000D6;

		case 28:
			return 0x0000D8;

		case 29:
			return 0x0000D9;

		case 30:
			return 0x0000DA;

		case 31:
			return 0x0000DB;

		case 32:
			return 0x000020;

		case 33:
			return 0x000021;

		case 34:
			return 0x000022;

		case 35:
			return 0x000023;

		case 36:
			return 0x000024;

		case 37:
			return 0x000025;

		case 38:
			return 0x000026;

		case 39:
			return 0x000027;

		case 40:
			return 0x000028;

		case 41:
			return 0x000029;

		case 42:
			return 0x00002A;

		case 43:
			return 0x00002B;

		case 44:
			return 0x00002C;

		case 45:
			return 0x00002D;

		case 46:
			return 0x00002E;

		case 47:
			return 0x00002F;

		case 48:
			return 0x000030;

		case 49:
			return 0x000031;

		case 50:
			return 0x000032;

		case 51:
			return 0x000033;

		case 52:
			return 0x000034;

		case 53:
			return 0x000035;

		case 54:
			return 0x000036;

		case 55:
			return 0x000037;

		case 56:
			return 0x000038;

		case 57:
			return 0x000039;

		case 58:
			return 0x00003A;

		case 59:
			return 0x00003B;

		case 60:
			return 0x00003C;

		case 61:
			return 0x00003D;

		case 62:
			return 0x00003E;

		case 63:
			return 0x00003F;

		case 64:
			return 0x000040;

		case 65:
			return 0x000041;

		case 66:
			return 0x000042;

		case 67:
			return 0x000043;

		case 68:
			return 0x000044;

		case 69:
			return 0x000045;

		case 70:
			return 0x000046;

		case 71:
			return 0x000047;

		case 72:
			return 0x000048;

		case 73:
			return 0x000049;

		case 74:
			return 0x00004A;

		case 75:
			return 0x00004B;

		case 76:
			return 0x00004C;

		case 77:
			return 0x00004D;

		case 78:
			return 0x00004E;

		case 79:
			return 0x00004F;

		case 80:
			return 0x000050;

		case 81:
			return 0x000051;

		case 82:
			return 0x000052;

		case 83:
			return 0x000053;

		case 84:
			return 0x000054;

		case 85:
			return 0x000055;

		case 86:
			return 0x000056;

		case 87:
			return 0x000057;

		case 88:
			return 0x000058;

		case 89:
			return 0x000059;

		case 90:
			return 0x00005A;

		case 91:
			return 0x00005B;

		case 92:
			return 0x00005C;

		case 93:
			return 0x00005D;

		case 94:
			return 0x00005E;

		case 95:
			return 0x00005F;

		case 96:
			return 0x000060;

		case 97:
			return 0x000061;

		case 98:
			return 0x000062;

		case 99:
			return 0x000063;

		case 100:
			return 0x000064;

		case 101:
			return 0x000065;

		case 102:
			return 0x000066;

		case 103:
			return 0x000067;

		case 104:
			return 0x000068;

		case 105:
			return 0x000069;

		case 106:
			return 0x00006A;

		case 107:
			return 0x00006B;

		case 108:
			return 0x00006C;

		case 109:
			return 0x00006D;

		case 110:
			return 0x00006E;

		case 111:
			return 0x00006F;

		case 112:
			return 0x000070;

		case 113:
			return 0x000071;

		case 114:
			return 0x000072;

		case 115:
			return 0x000073;

		case 116:
			return 0x000074;

		case 117:
			return 0x000075;

		case 118:
			return 0x000076;

		case 119:
			return 0x000077;

		case 120:
			return 0x000078;

		case 121:
			return 0x000079;

		case 122:
			return 0x00007A;

		case 123:
			return 0x00007B;

		case 124:
			return 0x00007C;

		case 125:
			return 0x00007D;

		case 126:
			return 0x00007E;

		case 127:
			return 0x0000DC;

		case 128:
			return 0x0000DD;

		case 129:
			return 0x0000DF;

		case 130:
			return 0x0000E0;

		case 131:
			return 0x0000E1;

		case 132:
			return 0x0000E2;

		case 133:
			return 0x0000E3;

		case 134:
			return 0x0000E4;

		case 135:
			return 0x0000E5;

		case 136:
			return 0x0000E6;

		case 137:
			return 0x0000E7;

		case 138:
			return 0x0000E8;

		case 139:
			return 0x0000E9;

		case 140:
			return 0x0000EA;

		case 141:
			return 0x0000EB;

		case 142:
			return 0x0000EC;

		case 143:
			return 0x0000ED;

		case 144:
			return 0x0000EE;

		case 145:
			return 0x0000EF;

		case 146:
			return 0x0000F1;

		case 147:
			return 0x0000F2;

		case 148:
			return 0x0000F3;

		case 149:
			return 0x0000F4;

		case 150:
			return 0x0000F5;

		case 151:
			return 0x0000F6;

		case 152:
			return 0x0000F8;

		case 153:
			return 0x0000F9;

		case 154:
			return 0x0000FA;

		case 155:
			return 0x0000FB;

		case 156:
			return 0x0000FC;

		case 157:
			return 0x0000FD;

		case 158:
			return 0x0000FF;

		case 159:
			return 0x000104;

		case 160:
			return 0x000105;

		case 161:
			return 0x000106;

		case 162:
			return 0x000107;

		case 163:
			return 0x00010C;

		case 164:
			return 0x00010D;

		case 165:
			return 0x00010E;

		case 166:
			return 0x00010F;

		case 167:
			return 0x000118;

		case 168:
			return 0x000119;

		case 169:
			return 0x00011A;

		case 170:
			return 0x00011B;

		case 171:
			return 0x00011E;

		case 172:
			return 0x00011F;

		case 173:
			return 0x000130;

		case 174:
			return 0x000131;

		case 175:
			return 0x000141;

		case 176:
			return 0x000142;

		case 177:
			return 0x000143;

		case 178:
			return 0x000144;

		case 179:
			return 0x000147;

		case 180:
			return 0x000148;

		case 181:
			return 0x000150;

		case 182:
			return 0x000151;

		case 183:
			return 0x000152;

		case 184:
			return 0x000153;

		case 185:
			return 0x000158;

		case 186:
			return 0x000159;

		case 187:
			return 0x00015A;

		case 188:
			return 0x00015B;

		case 189:
			return 0x00015E;

		case 190:
			return 0x00015F;

		case 191:
			return 0x000160;

		case 192:
			return 0x000161;

		case 193:
			return 0x000164;

		case 194:
			return 0x000165;

		case 195:
			return 0x00016E;

		case 196:
			return 0x00016F;

		case 197:
			return 0x000170;

		case 198:
			return 0x000171;

		case 199:
			return 0x000178;

		case 200:
			return 0x000179;

		case 201:
			return 0x00017A;

		case 202:
			return 0x00017B;

		case 203:
			return 0x00017C;

		case 204:
			return 0x00017D;

		case 205:
			return 0x00017E;

		case 206:
			return 0x000404;

		case 207:
			return 0x000411;

		case 208:
			return 0x000413;

		case 209:
			return 0x000414;

		case 210:
			return 0x000416;

		case 211:
			return 0x000417;

		case 212:
			return 0x000418;

		case 213:
			return 0x000419;

		case 214:
			return 0x00041B;

		case 215:
			return 0x00041F;

		case 216:
			return 0x000423;

		case 217:
			return 0x000424;

		case 218:
			return 0x000426;

		case 219:
			return 0x000427;

		case 220:
			return 0x000428;

		case 221:
			return 0x000429;

		case 222:
			return 0x00042A;

		case 223:
			return 0x00042B;

		case 224:
			return 0x00042C;

		case 225:
			return 0x00042D;

		case 226:
			return 0x00042E;

		case 227:
			return 0x00042F;

		case 228:
			return 0x000431;

		case 229:
			return 0x000432;

		case 230:
			return 0x000433;

		case 231:
			return 0x000434;

		case 232:
			return 0x000436;

		case 233:
			return 0x000437;

		case 234:
			return 0x000438;

		case 235:
			return 0x000439;

		case 236:
			return 0x00043A;

		case 237:
			return 0x00043B;

		case 238:
			return 0x00043C;

		case 239:
			return 0x00043D;

		case 240:
			return 0x00043F;

		case 241:
			return 0x000442;

		case 242:
			return 0x000444;

		case 243:
			return 0x000446;

		case 244:
			return 0x000447;

		case 245:
			return 0x000448;

		case 246:
			return 0x000449;

		case 247:
			return 0x00044A;

		case 248:
			return 0x00044B;

		case 249:
			return 0x00044C;

		case 250:
			return 0x00044D;

		case 251:
			return 0x00044E;

		case 252:
			return 0x00044F;

		case 253:
			return 0x000454;

		case 254:
			return 0x000490;

		case 255:
			return 0x000491;

		default:
			return {};
	}
}

}

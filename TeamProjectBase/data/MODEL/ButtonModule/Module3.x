xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 366;
 36.96441;17.43423;25.62603;,
 40.70078;16.58752;25.62603;,
 40.70078;16.58752;-24.76365;,
 36.96441;17.43423;-24.76365;,
 28.82653;32.69370;25.62603;,
 28.91101;28.59211;25.62603;,
 28.91101;28.59211;-24.76365;,
 28.82653;32.69370;-24.76365;,
 28.94596;35.72262;25.62603;,
 28.94596;35.72262;-24.76365;,
 33.70755;19.17501;-24.76365;,
 33.70755;19.17501;25.62603;,
 31.38958;21.68369;-24.76365;,
 31.38958;21.68369;25.62603;,
 29.91082;24.51949;-24.76365;,
 29.91082;24.51949;25.62603;,
 47.59379;16.64218;-24.76365;,
 44.16745;16.49729;-24.76365;,
 44.16745;16.49729;25.62603;,
 47.59379;16.64218;25.62603;,
 -47.53527;-39.68457;25.62603;,
 -48.53527;-39.41662;25.62603;,
 -48.53527;-39.41662;-24.76365;,
 -47.53527;-39.68457;-24.76365;,
 -49.26732;-38.68457;25.62603;,
 -49.26732;-38.68457;-24.76365;,
 -49.53527;-37.68457;25.62603;,
 -49.53527;-37.68457;-24.76365;,
 51.04739;-37.68457;25.62603;,
 50.77945;-38.68457;25.62603;,
 50.77945;-38.68457;-24.76365;,
 51.04739;-37.68457;-24.76365;,
 50.04743;-39.41662;25.62603;,
 50.04743;-39.41662;-24.76365;,
 49.04743;-39.68457;25.62603;,
 49.04743;-39.68457;-24.76365;,
 -47.53527;39.12840;-24.76365;,
 -48.53527;38.86045;-24.76365;,
 -48.53527;38.86045;25.62603;,
 -47.53527;39.12840;25.62603;,
 -49.26732;38.12840;-24.76365;,
 -49.26732;38.12840;25.62603;,
 -49.53527;37.12840;-24.76365;,
 -49.53527;37.12840;25.62603;,
 49.07491;16.89029;25.62603;,
 50.06117;16.78755;25.62603;,
 50.06117;16.78755;-24.76365;,
 49.07491;16.89029;-24.76365;,
 50.78314;16.17644;25.62603;,
 50.78314;16.17644;-24.76365;,
 51.04739;15.22070;25.62603;,
 51.04739;15.22070;-24.76365;,
 29.06404;37.13536;-24.76365;,
 28.87937;38.13188;-24.76365;,
 28.87937;38.13188;25.62603;,
 29.06404;37.13536;25.62603;,
 28.20830;38.86139;-24.76365;,
 28.20830;38.86139;25.62603;,
 27.23061;39.12840;-24.76365;,
 27.23061;39.12840;25.62603;,
 -49.53527;-6.07191;25.62603;,
 -49.53527;-3.05623;-24.76365;,
 51.04739;-2.91536;-24.76365;,
 51.04739;-5.93104;25.62603;,
 51.04739;-5.93104;25.62603;,
 51.04739;15.22070;25.62603;,
 50.78314;16.17644;25.62603;,
 50.06117;16.78755;25.62603;,
 49.07491;16.89029;25.62603;,
 47.59379;16.64218;25.62603;,
 44.16745;16.49729;25.62603;,
 40.70078;16.58752;25.62603;,
 36.96441;17.43423;25.62603;,
 33.70755;19.17501;25.62603;,
 31.38958;21.68369;25.62603;,
 29.91082;24.51949;25.62603;,
 28.91101;28.59211;25.62603;,
 28.82653;32.69370;25.62603;,
 28.94596;35.72262;25.62603;,
 29.06404;37.13536;25.62603;,
 28.87937;38.13188;25.62603;,
 28.20830;38.86139;25.62603;,
 27.23061;39.12840;25.62603;,
 -47.53527;39.12840;25.62603;,
 -48.53527;38.86045;25.62603;,
 -49.26732;38.12840;25.62603;,
 -49.53527;37.12840;25.62603;,
 -49.53527;-6.07191;25.62603;,
 -49.53527;-26.82833;-24.76365;,
 -49.53527;-26.62722;25.62603;,
 51.04739;-26.60850;25.62603;,
 51.04739;-26.80961;-24.76365;,
 -49.53527;-26.62722;25.62603;,
 -49.53527;-37.68457;25.62603;,
 -49.26732;-38.68457;25.62603;,
 -48.53527;-39.41662;25.62603;,
 -47.53527;-39.68457;25.62603;,
 49.04743;-39.68457;25.62603;,
 50.04743;-39.41662;25.62603;,
 50.77945;-38.68457;25.62603;,
 51.04739;-37.68457;25.62603;,
 51.04739;-26.60850;25.62603;,
 48.66286;-2.91870;-24.76365;,
 51.04739;-2.91536;-24.76365;,
 51.04739;-26.80961;-24.76365;,
 48.66286;-26.81006;-24.76365;,
 -49.53527;-3.05623;-24.76365;,
 -47.03019;-3.05272;-24.76365;,
 -47.03019;-26.82787;-24.76365;,
 -49.53527;-26.82833;-24.76365;,
 -49.53527;37.12840;-24.76365;,
 -49.26732;38.12840;-24.76365;,
 -48.53527;38.86045;-24.76365;,
 -47.53527;39.12840;-24.76365;,
 27.23061;39.12840;-24.76365;,
 28.20830;38.86139;-24.76365;,
 28.87937;38.13188;-24.76365;,
 29.06404;37.13536;-24.76365;,
 28.94596;35.72262;-24.76365;,
 28.82653;32.69370;-24.76365;,
 28.91101;28.59211;-24.76365;,
 29.91082;24.51949;-24.76365;,
 31.38958;21.68369;-24.76365;,
 33.70755;19.17501;-24.76365;,
 36.96441;17.43423;-24.76365;,
 40.70078;16.58752;-24.76365;,
 44.16745;16.49729;-24.76365;,
 47.59379;16.64218;-24.76365;,
 49.07491;16.89029;-24.76365;,
 50.06117;16.78755;-24.76365;,
 50.78314;16.17644;-24.76365;,
 51.04739;15.22070;-24.76365;,
 51.04739;-37.68457;-24.76365;,
 50.77945;-38.68457;-24.76365;,
 50.04743;-39.41662;-24.76365;,
 49.04743;-39.68457;-24.76365;,
 -47.53527;-39.68457;-24.76365;,
 -48.53527;-39.41662;-24.76365;,
 -49.26732;-38.68457;-24.76365;,
 -49.53527;-37.68457;-24.76365;,
 -47.03019;-26.82787;-24.76365;,
 48.66286;-2.91870;-21.07083;,
 -47.03019;-3.05272;-21.07083;,
 48.66286;-26.81006;-21.07083;,
 -47.03019;-26.82787;-21.07083;,
 -51.27103;39.81059;-29.56317;,
 52.44114;39.81059;-29.56317;,
 52.44114;-39.81059;-29.56317;,
 -51.27103;-39.81059;-29.56317;,
 52.44114;39.81059;-29.56317;,
 52.44114;39.81059;27.44039;,
 52.44114;-39.81059;27.44039;,
 52.44114;-39.81059;-29.56317;,
 52.44114;39.81059;27.44039;,
 -51.27103;39.81059;27.44039;,
 -51.27103;-39.81059;27.44039;,
 52.44114;-39.81059;27.44039;,
 -51.27103;39.81059;27.44039;,
 -51.27103;39.81059;-29.56317;,
 -51.27103;-39.81059;-29.56317;,
 -51.27103;-39.81059;27.44039;,
 52.44114;39.81059;-29.56317;,
 -51.27103;39.81059;-29.56317;,
 -51.27103;-39.81059;-29.56317;,
 52.44114;-39.81059;-29.56317;,
 -55.62416;44.87287;29.74654;,
 56.14483;44.87287;29.74654;,
 56.14483;-44.87287;29.74654;,
 -55.62416;-44.87287;29.74654;,
 7.17987;-0.07181;-24.71872;,
 2.89875;-0.07181;-24.71872;,
 2.89875;-0.07181;-27.45051;,
 7.17987;-0.07181;-27.45051;,
 2.89875;35.13209;-24.71871;,
 7.17987;35.13209;-24.71871;,
 7.17987;35.13209;-27.45051;,
 2.89875;35.13209;-27.45051;,
 -40.26475;-0.07181;-24.71872;,
 -40.26475;-0.07181;-27.45051;,
 -44.98949;-0.07181;-24.71872;,
 -44.98949;-0.07181;-27.45051;,
 -44.98949;35.13209;-24.71871;,
 -40.26475;35.13209;-24.71871;,
 -40.26475;35.13209;-27.45051;,
 -44.98949;35.13209;-27.45051;,
 -40.26475;-0.07181;-27.45051;,
 -40.26475;3.74030;-27.45051;,
 2.89876;3.74030;-27.45051;,
 2.89875;-0.07181;-27.45051;,
 -44.98949;-0.07181;-27.45051;,
 -44.98949;3.74030;-27.45051;,
 7.17987;3.74030;-27.45051;,
 7.17987;-0.07181;-27.45051;,
 -44.98949;3.74030;-27.45051;,
 -44.98949;-0.07181;-24.71872;,
 -44.98949;3.74030;-24.71872;,
 7.17987;3.74030;-27.45051;,
 7.17987;3.74030;-24.71872;,
 7.17987;-0.07181;-24.71872;,
 -44.98949;3.74030;-24.71872;,
 -44.98949;-0.07181;-24.71872;,
 -40.26475;-0.07181;-24.71872;,
 -40.26475;3.74030;-24.71872;,
 7.17987;-0.07181;-24.71872;,
 7.17987;3.74030;-24.71872;,
 2.89875;3.74030;-24.71872;,
 2.89875;-0.07181;-24.71872;,
 -40.26475;31.49744;-27.45051;,
 -40.26475;35.13209;-27.45051;,
 2.89875;35.13209;-27.45051;,
 2.89875;31.49744;-27.45051;,
 -44.98949;31.49744;-27.45051;,
 -44.98949;35.13209;-27.45051;,
 7.17987;31.49744;-27.45051;,
 7.17987;35.13209;-27.45051;,
 -44.98949;31.49744;-27.45051;,
 -44.98949;31.49744;-24.71871;,
 -44.98949;35.13209;-24.71871;,
 7.17987;31.49744;-27.45051;,
 7.17987;31.49744;-24.71871;,
 7.17987;35.13209;-24.71871;,
 -44.98949;35.13209;-24.71871;,
 -44.98949;31.49744;-24.71871;,
 -40.26475;31.49744;-24.71871;,
 -40.26475;35.13209;-24.71871;,
 7.17987;31.49744;-24.71871;,
 2.89875;31.49744;-24.71871;,
 7.17987;35.13209;-24.71871;,
 2.89875;35.13209;-24.71871;,
 -40.26475;31.49744;-24.79317;,
 -40.26475;3.74030;-24.79318;,
 2.89875;31.49744;-24.79317;,
 2.89876;3.74030;-24.79318;,
 48.64736;13.88423;-26.47354;,
 46.88266;13.88423;-26.47354;,
 46.88266;13.88423;-24.55111;,
 48.64736;13.88423;-24.55111;,
 46.88266;-0.08796;-26.47354;,
 48.64736;-0.08796;-26.47354;,
 48.64736;-0.08796;-24.55111;,
 46.88266;-0.08796;-24.55111;,
 41.06628;13.88423;-26.47354;,
 41.06628;13.88423;-24.55111;,
 41.06628;-0.08796;-26.47354;,
 41.06628;-0.08796;-24.55111;,
 36.86446;13.88423;-26.47354;,
 36.86446;13.88423;-24.55111;,
 36.86446;-0.08796;-26.47354;,
 36.86446;-0.08796;-24.55111;,
 30.91367;13.88423;-26.47354;,
 30.91367;13.88423;-24.55111;,
 30.91367;-0.08796;-26.47354;,
 30.91367;-0.08796;-24.55111;,
 26.78704;13.88423;-26.47354;,
 26.78704;13.88423;-24.55111;,
 26.78704;-0.08796;-26.47354;,
 26.78704;-0.08796;-24.55111;,
 21.04680;13.88423;-26.47354;,
 21.04680;13.88423;-24.55111;,
 21.04680;-0.08796;-26.47354;,
 21.04680;-0.08796;-24.55111;,
 16.92802;13.88423;-26.47354;,
 16.92802;13.88423;-24.55111;,
 16.92802;-0.08796;-26.47354;,
 16.92802;-0.08796;-24.55111;,
 10.04923;13.88423;-24.55111;,
 11.40843;13.88423;-24.55111;,
 11.40843;13.88423;-26.47354;,
 10.04923;13.88423;-26.47354;,
 11.40843;-0.08796;-24.55111;,
 11.40843;-0.08796;-26.47354;,
 10.04923;-0.08796;-24.55111;,
 10.04923;-0.08796;-26.47354;,
 11.40843;11.94899;-26.47354;,
 11.40843;13.88423;-26.47354;,
 16.92802;13.88423;-26.47354;,
 16.92802;11.94899;-26.47354;,
 10.04923;11.94899;-26.47354;,
 10.04923;13.88423;-26.47354;,
 21.04680;13.88423;-26.47354;,
 21.04680;11.94899;-26.47354;,
 10.04923;13.88423;-26.47354;,
 10.04923;11.94899;-26.47354;,
 10.04923;11.94899;-24.55111;,
 26.78704;13.88423;-26.47354;,
 26.78704;11.94899;-26.47354;,
 10.04923;13.88423;-24.55111;,
 10.04923;11.94899;-24.55111;,
 11.40843;11.94899;-24.55111;,
 11.40843;13.88423;-24.55111;,
 30.91367;13.88423;-26.47354;,
 30.91367;11.94899;-26.47354;,
 16.92802;11.94899;-24.55111;,
 16.92802;13.88423;-24.55111;,
 36.86446;13.88423;-26.47354;,
 36.86446;11.94899;-26.47354;,
 21.04680;11.94899;-24.55111;,
 21.04680;13.88423;-24.55111;,
 41.06628;13.88423;-26.47354;,
 41.06628;11.94899;-26.47354;,
 26.78704;11.94899;-24.55111;,
 26.78704;13.88423;-24.55111;,
 46.88266;13.88423;-26.47354;,
 46.88267;11.94899;-26.47354;,
 30.91367;11.94899;-24.55111;,
 30.91367;13.88423;-24.55111;,
 48.64736;13.88423;-26.47354;,
 48.64736;11.94899;-26.47354;,
 36.86446;11.94899;-24.55111;,
 36.86446;13.88423;-24.55111;,
 48.64736;11.94899;-26.47354;,
 48.64736;13.88423;-26.47354;,
 48.64736;11.94899;-24.55111;,
 41.06628;11.94899;-24.55111;,
 41.06628;13.88423;-24.55111;,
 48.64736;11.94899;-24.55111;,
 48.64736;13.88423;-24.55111;,
 46.88266;13.88423;-24.55111;,
 46.88267;11.94899;-24.55111;,
 11.40843;-0.08796;-26.47354;,
 11.40843;1.80581;-26.47354;,
 16.92802;1.80581;-26.47354;,
 16.92802;-0.08796;-26.47354;,
 10.04923;1.80581;-26.47354;,
 10.04923;-0.08796;-26.47354;,
 16.92802;1.80581;-26.47354;,
 21.04680;1.80581;-26.47354;,
 21.04680;-0.08796;-26.47354;,
 10.04923;1.80581;-26.47354;,
 10.04923;1.80581;-24.55111;,
 10.04923;-0.08796;-26.47354;,
 26.78704;1.80581;-26.47354;,
 26.78704;-0.08796;-26.47354;,
 10.04923;1.80581;-24.55111;,
 11.40843;1.80581;-24.55111;,
 10.04923;-0.08796;-24.55111;,
 11.40843;-0.08796;-24.55111;,
 30.91367;1.80581;-26.47354;,
 30.91367;-0.08796;-26.47354;,
 16.92802;-0.08796;-24.55111;,
 16.92802;1.80581;-24.55111;,
 36.86446;1.80581;-26.47354;,
 36.86446;-0.08796;-26.47354;,
 21.04680;1.80581;-24.55111;,
 21.04680;-0.08796;-24.55111;,
 41.06628;1.80581;-26.47354;,
 41.06628;-0.08796;-26.47354;,
 26.78704;-0.08796;-24.55111;,
 26.78704;1.80581;-24.55111;,
 46.88266;1.80581;-26.47354;,
 46.88266;-0.08796;-26.47354;,
 30.91367;1.80581;-24.55111;,
 30.91367;-0.08796;-24.55111;,
 48.64736;1.80581;-26.47354;,
 48.64736;-0.08796;-26.47354;,
 36.86446;-0.08796;-24.55111;,
 36.86446;1.80581;-24.55111;,
 48.64736;-0.08796;-26.47354;,
 48.64736;1.80581;-26.47354;,
 48.64736;1.80581;-24.55111;,
 41.06628;1.80581;-24.55111;,
 41.06628;-0.08796;-24.55111;,
 48.64736;-0.08796;-24.55111;,
 48.64736;1.80581;-24.55111;,
 46.88266;1.80581;-24.55111;,
 46.88266;-0.08796;-24.55111;;
 
 157;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;3,10,11,0;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,6,5,15;,
 4;16,17,18,19;,
 4;17,2,1,18;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;28,29,30,31;,
 4;29,32,33,30;,
 4;32,34,35,33;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;40,42,43,41;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;48,50,51,49;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 4;23,35,34,20;,
 4;39,59,58,36;,
 4;19,44,47,16;,
 4;55,8,9,52;,
 4;60,43,42,61;,
 4;62,51,50,63;,
 24;64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87;,
 4;88,27,26,89;,
 4;89,60,61,88;,
 4;90,28,31,91;,
 4;91,62,63,90;,
 10;92,93,94,95,96,97,98,99,100,101;,
 4;101,64,87,92;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 26;106,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,103,102,107;,
 12;104,132,133,134,135,136,137,138,139,109,140,105;,
 4;141,142,107,102;,
 4;143,141,102,105;,
 4;144,143,105,108;,
 4;142,144,108,107;,
 4;142,141,143,144;,
 4;145,146,147,148;,
 4;149,150,151,152;,
 4;153,154,155,156;,
 4;157,158,159,160;,
 4;157,150,161,162;,
 4;163,164,151,160;,
 4;165,166,167,168;,
 4;169,170,171,172;,
 4;173,174,175,176;,
 4;170,177,178,171;,
 4;177,179,180,178;,
 4;181,182,183,184;,
 4;182,173,176,183;,
 4;185,186,187,188;,
 4;186,185,189,190;,
 4;188,187,191,192;,
 4;193,180,194,195;,
 4;172,196,197,198;,
 4;199,200,201,202;,
 4;203,204,205,206;,
 4;202,201,206,205;,
 4;207,208,209,210;,
 4;208,207,211,212;,
 4;207,186,190,211;,
 4;187,210,213,191;,
 4;210,209,214,213;,
 4;184,215,216,217;,
 4;215,193,195,216;,
 4;196,218,219,197;,
 4;218,175,220,219;,
 4;221,222,223,224;,
 4;222,199,202,223;,
 4;204,225,226,205;,
 4;225,227,228,226;,
 4;224,223,226,228;,
 4;223,202,205,226;,
 4;229,230,186,207;,
 4;231,229,207,210;,
 4;232,231,210,187;,
 4;230,232,187,186;,
 4;230,229,231,232;,
 4;233,234,235,236;,
 4;237,238,239,240;,
 4;234,241,242,235;,
 4;243,237,240,244;,
 4;241,245,246,242;,
 4;247,243,244,248;,
 4;245,249,250,246;,
 4;251,247,248,252;,
 4;249,253,254,250;,
 4;255,251,252,256;,
 4;253,257,258,254;,
 4;259,255,256,260;,
 4;257,261,262,258;,
 4;263,259,260,264;,
 4;265,266,267,268;,
 4;266,262,261,267;,
 4;264,269,270,263;,
 4;269,271,272,270;,
 4;273,274,275,276;,
 4;274,273,277,278;,
 4;276,275,279,280;,
 4;281,282,283,265;,
 4;280,279,284,285;,
 4;286,287,288,289;,
 4;285,284,290,291;,
 4;289,288,292,293;,
 4;291,290,294,295;,
 4;293,292,296,297;,
 4;295,294,298,299;,
 4;297,296,300,301;,
 4;299,298,302,303;,
 4;301,300,304,305;,
 4;303,302,306,307;,
 4;305,304,308,309;,
 4;310,311,236,312;,
 4;309,308,313,314;,
 4;315,316,317,318;,
 4;314,313,318,317;,
 4;319,320,321,322;,
 4;273,320,323,277;,
 4;320,319,324,323;,
 4;322,325,326,327;,
 4;325,276,280,326;,
 4;282,328,329,283;,
 4;328,330,271,329;,
 4;327,326,331,332;,
 4;287,333,334,288;,
 4;333,335,336,334;,
 4;332,331,337,338;,
 4;331,285,291,337;,
 4;334,336,339,340;,
 4;338,337,341,342;,
 4;292,340,343,296;,
 4;340,339,344,343;,
 4;342,341,345,346;,
 4;341,295,299,345;,
 4;343,344,347,348;,
 4;346,345,349,350;,
 4;300,348,351,304;,
 4;348,347,352,351;,
 4;350,349,353,354;,
 4;349,303,307,353;,
 4;351,352,355,356;,
 4;357,358,359,239;,
 4;358,310,312,359;,
 4;308,356,360,313;,
 4;356,355,361,360;,
 4;362,363,364,365;,
 4;363,315,318,364;,
 4;360,361,365,364;;
 
 MeshMaterialList {
  3;
  157;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;0.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.548800;0.612000;0.696800;1.000000;;
   3.750000;
   0.350000;0.350000;0.350000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  0.349329;0.937000;0.000000;,
  0.124114;0.992268;0.000000;,
  0.999956;-0.009408;0.000000;,
  0.991476;0.130293;0.000000;,
  0.998116;-0.061359;0.000000;,
  0.611438;0.791293;0.000000;,
  0.817761;0.575559;0.000000;,
  0.935649;0.352931;0.000000;,
  -0.103929;0.994585;0.000000;,
  -0.008120;0.999967;0.000000;,
  -0.130527;-0.991445;-0.000000;,
  -0.500001;-0.866025;-0.000000;,
  -0.866025;-0.500001;-0.000000;,
  -0.991445;-0.130527;0.000000;,
  0.991445;-0.130524;0.000000;,
  0.866031;-0.499990;0.000000;,
  0.500009;-0.866020;0.000000;,
  0.130527;-0.991445;0.000000;,
  -0.130527;0.991445;0.000000;,
  -0.500001;0.866025;0.000000;,
  -0.866025;0.500001;0.000000;,
  -0.991445;0.130527;0.000000;,
  -0.031082;0.999517;0.000000;,
  0.392284;0.919844;0.000000;,
  0.842407;0.538842;0.000000;,
  0.990918;0.134470;0.000000;,
  0.998754;0.049901;0.000000;,
  0.894509;0.447051;0.000000;,
  0.520001;0.854166;0.000000;,
  0.132910;0.991128;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.001401;-0.999999;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000186;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;-0.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;;
  157;
  4;0,1,1,0;,
  4;2,3,3,2;,
  4;4,2,2,4;,
  4;0,5,5,0;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,3,3,7;,
  4;8,9,9,8;,
  4;9,1,1,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;10,17,17,10;,
  4;18,29,29,18;,
  4;8,22,22,8;,
  4;26,4,4,26;,
  4;30,21,21,31;,
  4;32,25,25,32;,
  24;33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,34,33,33,34,33;,
  4;35,13,13,36;,
  4;36,30,31,35;,
  4;32,14,14,32;,
  4;32,32,32,32;,
  10;34,34,33,33,34,34,33,33,33,33;,
  4;33,33,33,34;,
  4;37,38,39,40;,
  4;41,42,43,44;,
  26;41,45,46,46,45,47,48,49,47,47,47,46,47,49,47,47,47,47,47,47,46,47,45,38,37,42;,
  12;39,50,50,51,52,52,53,53,52,44,43,40;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;32,32,32,32;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;68,68,68,69;,
  4;70,70,71,70;,
  4;72,73,73,72;,
  4;73,72,72,73;,
  4;72,73,73,72;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;68,68,69,68;,
  4;70,70,70,71;,
  4;70,70,70,70;,
  4;73,72,72,73;,
  4;72,72,72,72;,
  4;72,72,72,72;,
  4;72,73,73,72;,
  4;73,72,72,73;,
  4;72,72,72,72;,
  4;70,70,70,70;,
  4;65,65,65,65;,
  4;74,74,74,74;,
  4;66,66,66,66;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;;
 }
 MeshTextureCoords {
  366;
  0.878672;0.258068;,
  0.919115;0.309682;,
  0.169115;0.559682;,
  0.253672;0.633068;,
  0.757344;0.103227;,
  0.797787;0.154841;,
  0.422787;0.779841;,
  0.507344;0.853227;,
  0.716902;0.051614;,
  0.591902;0.926614;,
  0.295951;0.669761;,
  0.858451;0.232261;,
  0.338230;0.706455;,
  0.838230;0.206455;,
  0.380508;0.743148;,
  0.818008;0.180648;,
  0.084557;0.486295;,
  0.126836;0.522989;,
  0.939336;0.335489;,
  0.959557;0.361295;,
  0.019884;1.000000;,
  0.013256;0.991541;,
  0.346589;0.324874;,
  0.019884;0.000000;,
  0.006628;0.983082;,
  0.673295;0.649749;,
  0.000000;0.974623;,
  1.000000;0.974623;,
  1.000000;0.979366;,
  0.993372;0.986244;,
  0.326705;0.652911;,
  0.000000;0.979366;,
  0.986744;0.993122;,
  0.653411;0.326455;,
  0.980116;1.000000;,
  0.980116;0.000000;,
  0.017176;1.000000;,
  0.344784;0.675125;,
  0.011451;0.008459;,
  0.017176;0.000000;,
  0.672392;0.350251;,
  0.005725;0.016918;,
  1.000000;0.025377;,
  0.000000;0.025377;,
  0.976901;0.383430;,
  0.984601;0.400135;,
  0.032196;0.447730;,
  0.048294;0.454823;,
  0.992301;0.416839;,
  0.016098;0.440636;,
  1.000000;0.433543;,
  0.000000;0.433543;,
  0.626977;0.957055;,
  0.637745;0.971370;,
  0.686512;0.020136;,
  0.700126;0.030204;,
  0.648514;0.985685;,
  0.672897;0.010068;,
  0.659283;1.000000;,
  0.659283;0.000000;,
  0.000000;0.573514;,
  1.000000;0.535250;,
  0.000000;0.620653;,
  1.000000;0.651765;,
  0.000000;0.651765;,
  0.000000;0.433543;,
  0.003095;0.419277;,
  0.011549;0.400934;,
  0.023098;0.383430;,
  0.040443;0.361295;,
  0.060664;0.335489;,
  0.080885;0.309682;,
  0.121328;0.258068;,
  0.141549;0.232261;,
  0.161770;0.206455;,
  0.181992;0.180648;,
  0.202213;0.154841;,
  0.242656;0.103227;,
  0.283098;0.051614;,
  0.299874;0.030204;,
  0.314008;0.015102;,
  0.328958;0.004047;,
  0.340717;0.000000;,
  0.982824;0.000000;,
  0.989849;0.003207;,
  0.997336;0.012688;,
  1.000000;0.025377;,
  1.000000;0.573514;,
  1.000000;0.836877;,
  0.000000;0.834325;,
  1.000000;0.865094;,
  0.000000;0.867169;,
  1.000000;0.834325;,
  1.000000;0.974623;,
  0.997336;0.987312;,
  0.990058;0.996600;,
  0.980116;1.000000;,
  0.019884;1.000000;,
  0.009942;0.996600;,
  0.002344;0.987017;,
  0.000000;0.979366;,
  0.000000;0.865094;,
  0.976292;0.618628;,
  1.000000;0.620653;,
  1.000000;0.867169;,
  0.976292;0.866451;,
  0.000000;0.535250;,
  0.024906;0.537377;,
  0.024906;0.837631;,
  0.000000;0.836877;,
  0.000000;0.025377;,
  0.002722;0.012635;,
  0.010158;0.003201;,
  0.017176;0.000000;,
  0.659283;0.000000;,
  0.671042;0.004047;,
  0.685992;0.015102;,
  0.700126;0.030204;,
  0.716902;0.051614;,
  0.757344;0.103227;,
  0.797787;0.154841;,
  0.818008;0.180648;,
  0.838230;0.206455;,
  0.858451;0.232261;,
  0.878672;0.258068;,
  0.919115;0.309682;,
  0.939336;0.335489;,
  0.959557;0.361295;,
  0.976901;0.383430;,
  0.989640;0.412152;,
  0.997373;0.423683;,
  1.000000;0.433543;,
  1.000000;0.979366;,
  0.997336;0.989683;,
  0.990058;0.997235;,
  0.980116;1.000000;,
  0.019884;1.000000;,
  0.009942;0.997235;,
  0.002722;0.987258;,
  0.000000;0.974623;,
  0.024906;0.837631;,
  0.976292;0.618628;,
  0.024906;0.537377;,
  0.976292;0.866451;,
  0.024906;0.837631;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.932027;1.000000;,
  0.932027;0.000000;,
  1.000000;0.000000;,
  0.932027;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.932027;1.000000;,
  0.075016;1.000000;,
  0.075016;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.075016;0.000000;,
  0.075016;1.000000;,
  0.000000;1.000000;,
  0.924984;0.000000;,
  0.924984;0.132438;,
  0.067973;0.132438;,
  0.067973;0.000000;,
  1.000000;0.000000;,
  1.000000;0.132438;,
  0.000000;0.132438;,
  0.000000;0.000000;,
  0.000000;0.132438;,
  1.000000;0.000000;,
  1.000000;0.132438;,
  1.000000;0.132438;,
  0.000000;0.132438;,
  0.000000;0.000000;,
  0.000000;0.132438;,
  0.000000;0.000000;,
  0.075016;0.000000;,
  0.075016;0.132438;,
  1.000000;0.000000;,
  1.000000;0.132438;,
  0.932027;0.132438;,
  0.932027;0.000000;,
  0.924984;0.873727;,
  0.924984;1.000000;,
  0.067973;1.000000;,
  0.067973;0.873727;,
  1.000000;0.873727;,
  1.000000;1.000000;,
  0.000000;0.873727;,
  0.000000;1.000000;,
  0.000000;0.873727;,
  1.000000;0.873727;,
  1.000000;1.000000;,
  1.000000;0.873727;,
  0.000000;0.873727;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.873727;,
  0.075016;0.873727;,
  0.075016;1.000000;,
  1.000000;0.873727;,
  0.932027;0.873727;,
  1.000000;1.000000;,
  0.932027;1.000000;,
  0.924984;0.873727;,
  0.924984;0.132438;,
  0.067973;0.873727;,
  0.067973;0.132438;,
  1.000000;1.000000;,
  0.954280;1.000000;,
  0.954280;0.000000;,
  1.000000;0.000000;,
  0.954280;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.954280;1.000000;,
  0.803590;1.000000;,
  0.803590;0.000000;,
  0.803590;0.000000;,
  0.803590;1.000000;,
  0.694729;1.000000;,
  0.694729;0.000000;,
  0.694729;0.000000;,
  0.694729;1.000000;,
  0.540556;1.000000;,
  0.540556;0.000000;,
  0.540556;0.000000;,
  0.540556;1.000000;,
  0.433643;1.000000;,
  0.433643;0.000000;,
  0.433643;0.000000;,
  0.433643;1.000000;,
  0.284925;1.000000;,
  0.284925;0.000000;,
  0.284925;0.000000;,
  0.284925;1.000000;,
  0.178216;1.000000;,
  0.178216;0.000000;,
  0.178216;0.000000;,
  0.178216;1.000000;,
  0.000000;0.000000;,
  0.035214;0.000000;,
  0.035214;1.000000;,
  0.000000;1.000000;,
  0.035214;1.000000;,
  0.035214;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.035214;0.138507;,
  0.035214;0.000000;,
  0.178216;0.000000;,
  0.178216;0.138507;,
  0.000000;0.138507;,
  0.000000;0.000000;,
  0.284925;0.000000;,
  0.284925;0.138507;,
  1.000000;0.000000;,
  1.000000;0.138507;,
  0.000000;0.138507;,
  0.433643;0.000000;,
  0.433643;0.138507;,
  1.000000;0.000000;,
  1.000000;0.138507;,
  0.964786;0.138507;,
  0.964786;0.000000;,
  0.540556;0.000000;,
  0.540556;0.138507;,
  0.821784;0.138507;,
  0.821784;0.000000;,
  0.694729;0.000000;,
  0.694729;0.138507;,
  0.715075;0.138507;,
  0.715075;0.000000;,
  0.803590;0.000000;,
  0.803590;0.138507;,
  0.566357;0.138507;,
  0.566357;0.000000;,
  0.954280;0.000000;,
  0.954280;0.138507;,
  0.459444;0.138507;,
  0.459444;0.000000;,
  1.000000;0.000000;,
  1.000000;0.138507;,
  0.305271;0.138507;,
  0.305271;0.000000;,
  0.000000;0.138507;,
  0.000000;0.000000;,
  1.000000;0.138507;,
  0.196410;0.138507;,
  0.196410;0.000000;,
  0.000000;0.138507;,
  0.000000;0.000000;,
  0.045720;0.000000;,
  0.045720;0.138507;,
  0.035214;1.000000;,
  0.035214;0.864461;,
  0.178216;0.864461;,
  0.178216;1.000000;,
  0.000000;0.864461;,
  0.000000;1.000000;,
  0.178216;0.864461;,
  0.284925;0.864461;,
  0.284925;1.000000;,
  1.000000;0.864461;,
  0.000000;0.864461;,
  1.000000;1.000000;,
  0.433643;0.864461;,
  0.433643;1.000000;,
  1.000000;0.864461;,
  0.964786;0.864461;,
  1.000000;1.000000;,
  0.964786;1.000000;,
  0.540556;0.864461;,
  0.540556;1.000000;,
  0.821784;1.000000;,
  0.821784;0.864461;,
  0.694729;0.864461;,
  0.694729;1.000000;,
  0.715075;0.864461;,
  0.715075;1.000000;,
  0.803590;0.864461;,
  0.803590;1.000000;,
  0.566357;1.000000;,
  0.566357;0.864461;,
  0.954280;0.864461;,
  0.954280;1.000000;,
  0.459444;0.864461;,
  0.459444;1.000000;,
  1.000000;0.864461;,
  1.000000;1.000000;,
  0.305271;1.000000;,
  0.305271;0.864461;,
  0.000000;1.000000;,
  0.000000;0.864461;,
  1.000000;0.864461;,
  0.196410;0.864461;,
  0.196410;1.000000;,
  0.000000;1.000000;,
  0.000000;0.864461;,
  0.045720;0.864461;,
  0.045720;1.000000;;
 }
}

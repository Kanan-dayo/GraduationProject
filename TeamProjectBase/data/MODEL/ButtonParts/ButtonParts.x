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
 168;
 35.89941;17.49480;25.79036;,
 39.63579;16.64810;25.79036;,
 39.63579;16.64810;-24.59934;,
 35.89941;17.49480;-24.59934;,
 27.76154;32.75431;25.79036;,
 27.84602;28.65270;25.79036;,
 27.84602;28.65270;-24.59934;,
 27.76154;32.75431;-24.59934;,
 27.88098;35.78324;25.79036;,
 27.88098;35.78324;-24.59934;,
 32.64255;19.23558;-24.59934;,
 32.64255;19.23558;25.79036;,
 30.32459;21.74426;-24.59934;,
 30.32459;21.74426;25.79036;,
 28.84583;24.58006;-24.59934;,
 28.84583;24.58006;25.79036;,
 46.52880;16.70276;-24.59934;,
 43.10245;16.55787;-24.59934;,
 43.10245;16.55787;25.79036;,
 46.52880;16.70276;25.79036;,
 -48.60028;-39.62402;25.79036;,
 -49.60026;-39.35606;25.79036;,
 -49.60026;-39.35606;-24.59934;,
 -48.60028;-39.62402;-24.59934;,
 -50.33229;-38.62401;25.79036;,
 -50.33229;-38.62401;-24.59934;,
 -50.60025;-37.62401;25.79036;,
 -50.60025;-37.62401;-24.59934;,
 49.98243;-37.62401;25.79036;,
 49.71448;-38.62401;25.79036;,
 49.71448;-38.62401;-24.59934;,
 49.98243;-37.62401;-24.59934;,
 48.98243;-39.35606;25.79036;,
 48.98243;-39.35606;-24.59934;,
 47.98243;-39.62402;25.79036;,
 47.98243;-39.62402;-24.59934;,
 -48.60028;39.18902;-24.59934;,
 -49.60026;38.92107;-24.59934;,
 -49.60026;38.92107;25.79036;,
 -48.60028;39.18902;25.79036;,
 -50.33229;38.18902;-24.59934;,
 -50.33229;38.18902;25.79036;,
 -50.60025;37.18902;-24.59934;,
 -50.60025;37.18902;25.79036;,
 48.00991;16.95086;25.79036;,
 48.99617;16.84812;25.79036;,
 48.99617;16.84812;-24.59934;,
 48.00991;16.95086;-24.59934;,
 49.71816;16.23701;25.79036;,
 49.71816;16.23701;-24.59934;,
 49.98243;15.28128;25.79036;,
 49.98243;15.28128;-24.59934;,
 27.99905;37.19598;-24.59934;,
 27.81439;38.19250;-24.59934;,
 27.81439;38.19250;25.79036;,
 27.99905;37.19598;25.79036;,
 27.14332;38.92201;-24.59934;,
 27.14332;38.92201;25.79036;,
 26.16563;39.18902;-24.59934;,
 26.16563;39.18902;25.79036;,
 -46.24096;-39.62402;25.79036;,
 -42.71490;-39.62402;-24.59934;,
 -42.70948;39.18902;-24.59934;,
 -46.23553;39.18902;25.79036;,
 -46.23553;39.18902;25.79036;,
 -48.60028;39.18902;25.79036;,
 -49.60026;38.92107;25.79036;,
 -50.33229;38.18902;25.79036;,
 -50.60025;37.18902;25.79036;,
 -50.60025;-37.62401;25.79036;,
 -50.33229;-38.62401;25.79036;,
 -49.60026;-39.35606;25.79036;,
 -48.60028;-39.62402;25.79036;,
 -46.24096;-39.62402;25.79036;,
 19.94575;-39.62402;-24.59934;,
 22.76454;-39.62402;25.79036;,
 22.82486;39.18902;25.79036;,
 20.00608;39.18902;-24.59934;,
 22.76454;-39.62402;25.79036;,
 47.98243;-39.62402;25.79036;,
 48.98243;-39.35606;25.79036;,
 49.71448;-38.62401;25.79036;,
 49.98243;-37.62401;25.79036;,
 49.98243;15.28128;25.79036;,
 49.71816;16.23701;25.79036;,
 48.99617;16.84812;25.79036;,
 48.00991;16.95086;25.79036;,
 46.52880;16.70276;25.79036;,
 43.10245;16.55787;25.79036;,
 39.63579;16.64810;25.79036;,
 35.89941;17.49480;25.79036;,
 32.64255;19.23558;25.79036;,
 30.32459;21.74426;25.79036;,
 28.84583;24.58006;25.79036;,
 27.84602;28.65270;25.79036;,
 27.76154;32.75431;25.79036;,
 27.88098;35.78324;25.79036;,
 27.99905;37.19598;25.79036;,
 27.81439;38.19250;25.79036;,
 27.14332;38.92201;25.79036;,
 26.16563;39.18902;25.79036;,
 22.82486;39.18902;25.79036;,
 -42.71490;-39.62402;-24.59934;,
 -42.71437;-31.88744;-24.59934;,
 19.95167;-31.88744;-24.59934;,
 19.94575;-39.62402;-24.59934;,
 -42.71007;30.60302;-24.59934;,
 -42.70948;39.18902;-24.59934;,
 20.00608;39.18902;-24.59934;,
 19.99951;30.60302;-24.59934;,
 -48.60028;-39.62402;-24.59934;,
 -49.60026;-39.35606;-24.59934;,
 -50.33229;-38.62401;-24.59934;,
 -50.60025;-37.62401;-24.59934;,
 -50.60025;37.18902;-24.59934;,
 -50.33229;38.18902;-24.59934;,
 -49.60026;38.92107;-24.59934;,
 -48.60028;39.18902;-24.59934;,
 26.16563;39.18902;-24.59934;,
 27.14332;38.92201;-24.59934;,
 27.81439;38.19250;-24.59934;,
 27.99905;37.19598;-24.59934;,
 27.88098;35.78324;-24.59934;,
 27.76154;32.75431;-24.59934;,
 27.84602;28.65270;-24.59934;,
 28.84583;24.58006;-24.59934;,
 30.32459;21.74426;-24.59934;,
 32.64255;19.23558;-24.59934;,
 35.89941;17.49480;-24.59934;,
 39.63579;16.64810;-24.59934;,
 43.10245;16.55787;-24.59934;,
 46.52880;16.70276;-24.59934;,
 48.00991;16.95086;-24.59934;,
 48.99617;16.84812;-24.59934;,
 49.71816;16.23701;-24.59934;,
 49.98243;15.28128;-24.59934;,
 49.98243;-37.62401;-24.59934;,
 49.71448;-38.62401;-24.59934;,
 48.98243;-39.35606;-24.59934;,
 47.98243;-39.62402;-24.59934;,
 -42.71007;30.60302;-19.18946;,
 -42.71437;-31.88744;-19.18946;,
 19.99951;30.60302;-19.18946;,
 19.95167;-31.88744;-19.18946;,
 -51.85610;39.81059;-29.56317;,
 51.85610;39.81059;-29.56317;,
 51.85610;-39.81059;-29.56317;,
 -51.85610;-39.81059;-29.56317;,
 51.85610;39.81059;-29.56317;,
 51.85610;39.81059;27.44039;,
 51.85610;-39.81059;27.44039;,
 51.85610;-39.81059;-29.56317;,
 51.85610;39.81059;27.44039;,
 -51.85610;39.81059;27.44039;,
 -51.85610;-39.81059;27.44039;,
 51.85610;-39.81059;27.44039;,
 -51.85610;39.81059;27.44039;,
 -51.85610;39.81059;-29.56317;,
 -51.85610;-39.81059;-29.56317;,
 -51.85610;-39.81059;27.44039;,
 51.85610;39.81059;-29.56317;,
 -51.85610;39.81059;-29.56317;,
 -51.85610;-39.81059;-29.56317;,
 51.85610;-39.81059;-29.56317;,
 -56.20919;44.87287;29.74654;,
 55.55979;44.87287;29.74654;,
 55.55979;-44.87287;29.74654;,
 -56.20919;-44.87287;29.74654;;
 
 53;
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
 4;43,42,27,26;,
 4;51,50,28,31;,
 4;19,44,47,16;,
 4;55,8,9,52;,
 4;60,20,23,61;,
 4;62,36,39,63;,
 10;64,65,66,67,68,69,70,71,72,73;,
 4;74,35,34,75;,
 4;75,60,61,74;,
 4;76,59,58,77;,
 4;77,62,63,76;,
 24;78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101;,
 4;101,64,73,78;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 12;102,110,111,112,113,114,115,116,117,107,106,103;,
 26;108,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,105,104,109;,
 4;140,141,103,106;,
 4;142,140,106,109;,
 4;143,142,109,104;,
 4;141,143,104,103;,
 4;141,140,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;156,149,160,161;,
 4;162,163,150,159;,
 4;164,165,166,167;;
 
 MeshMaterialList {
  3;
  53;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  2;;
  Material {
   0.548800;0.612000;0.696800;1.000000;;
   3.750000;
   0.350000;0.350000;0.350000;;
   0.000000;0.000000;0.000000;;
  }
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
 }
 MeshNormals {
  72;
  0.349329;0.937000;0.000000;,
  0.124114;0.992268;0.000000;,
  0.999956;-0.009408;0.000000;,
  0.991476;0.130292;0.000000;,
  0.998116;-0.061358;0.000000;,
  0.611438;0.791292;0.000000;,
  0.817761;0.575558;0.000000;,
  0.935650;0.352931;0.000000;,
  -0.103929;0.994585;0.000000;,
  -0.008120;0.999967;0.000000;,
  -0.130531;-0.991444;-0.000000;,
  -0.500012;-0.866019;-0.000000;,
  -0.866028;-0.499996;-0.000000;,
  -0.991444;-0.130530;-0.000000;,
  0.991445;-0.130527;0.000000;,
  0.866026;-0.499999;0.000000;,
  0.500005;-0.866023;0.000000;,
  0.130530;-0.991444;0.000000;,
  -0.130528;0.991445;0.000000;,
  -0.500007;0.866021;0.000000;,
  -0.866027;0.499998;0.000000;,
  -0.991444;0.130530;0.000000;,
  -0.031082;0.999517;0.000000;,
  0.392276;0.919847;0.000000;,
  0.842400;0.538852;0.000000;,
  0.990917;0.134473;0.000000;,
  0.998754;0.049902;0.000000;,
  0.894510;0.447048;0.000000;,
  0.520003;0.854165;0.000000;,
  0.132909;0.991128;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;-0.000069;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -1.000000;0.000765;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;;
  53;
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
  4;21,21,13,13;,
  4;25,25,14,14;,
  4;8,22,22,8;,
  4;26,4,4,26;,
  4;30,10,10,31;,
  4;32,18,18,33;,
  10;34,34,35,34,34,34,34,34,34,34;,
  4;36,17,17,37;,
  4;37,30,31,36;,
  4;38,29,29,39;,
  4;39,32,33,38;,
  24;40,41,41,42,42,41,41,41,42,43,41,42,44,42,43,42,45,42,41,46,47,47,42,48;,
  4;48,34,34,40;,
  4;49,49,50,51;,
  4;49,49,52,53;,
  12;49,49,49,49,49,49,49,54,49,49,49,49;,
  26;52,55,56,56,55,55,55,57,55,55,55,55,55,55,55,55,55,58,55,59,55,55,60,51,50,53;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;49,49,54,49;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;;
 }
 MeshTextureCoords {
  168;
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
  0.043341;1.000000;,
  0.078397;0.000000;,
  0.067768;1.000000;,
  0.037485;0.000000;,
  0.962515;0.000000;,
  0.982824;0.000000;,
  0.989849;0.003207;,
  0.997336;0.012688;,
  1.000000;0.025377;,
  1.000000;0.974623;,
  0.997336;0.987312;,
  0.990058;0.996600;,
  0.980116;1.000000;,
  0.956659;1.000000;,
  0.701373;0.000000;,
  0.729398;1.000000;,
  0.630592;0.000000;,
  0.606383;1.000000;,
  0.270602;1.000000;,
  0.019884;1.000000;,
  0.009942;0.996600;,
  0.002344;0.987017;,
  0.000000;0.979366;,
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
  0.369408;0.000000;,
  0.078397;1.000000;,
  0.077354;0.901836;,
  0.692049;0.901836;,
  0.701373;1.000000;,
  0.068926;0.108941;,
  0.067768;0.000000;,
  0.606383;0.000000;,
  0.616732;0.108941;,
  0.019884;1.000000;,
  0.009942;0.997235;,
  0.002722;0.987258;,
  0.000000;0.974623;,
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
  0.068926;0.108941;,
  0.077354;0.901836;,
  0.616732;0.108941;,
  0.692049;0.901836;,
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
  0.000000;1.000000;;
 }
}

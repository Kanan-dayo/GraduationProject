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
 31;
 -0.87349;29.62829;1.27507;,
 -8.47149;27.49093;-0.51365;,
 -11.61868;27.49093;1.27507;,
 -0.87349;29.62829;1.27507;,
 -0.87349;27.49093;-1.25456;,
 -14.91275;21.40428;-2.03004;,
 -20.72803;21.40428;1.27507;,
 -0.87349;21.40428;-3.39906;,
 -19.21668;12.29493;-3.04325;,
 -26.81466;12.29493;1.27507;,
 -0.87349;12.29493;-4.83198;,
 -20.72803;1.54973;-3.39906;,
 -28.95204;1.54973;1.27507;,
 -0.48539;1.34075;-5.33999;,
 -0.48539;1.34075;-5.33999;,
 -28.95204;1.54973;1.27507;,
 -20.72803;1.54973;-3.39906;,
 -1.45738;1.30652;1.29926;,
 -19.21668;12.29493;-3.04325;,
 -0.45897;12.14603;1.26862;,
 -26.81466;12.29493;1.27507;,
 -14.91275;21.40428;-2.03004;,
 -1.43875;17.68587;1.04826;,
 -20.72803;21.40428;1.27507;,
 -0.87349;21.40428;-3.39906;,
 -0.87349;12.29493;-4.83198;,
 -8.47149;27.49093;-0.51365;,
 -0.88867;24.41375;1.30650;,
 -11.61868;27.49093;1.27507;,
 -0.87349;27.49093;-1.25456;,
 -0.87349;29.62829;1.27507;;
 
 31;
 3;0,1,2;,
 3;3,4,1;,
 4;2,1,5,6;,
 4;1,4,7,5;,
 4;6,5,8,9;,
 4;5,7,10,8;,
 4;9,8,11,12;,
 4;8,10,13,11;,
 3;14,15,16;,
 3;14,17,15;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,22,21;,
 3;25,19,18;,
 3;25,17,14;,
 3;17,20,15;,
 3;24,19,25;,
 3;19,23,20;,
 3;19,17,25;,
 3;17,19,20;,
 3;26,27,28;,
 3;29,27,26;,
 3;29,22,24;,
 3;22,28,23;,
 3;22,19,24;,
 3;19,22,23;,
 3;30,27,26;,
 3;30,27,29;,
 3;27,30,28;,
 3;27,22,29;,
 3;22,27,28;;
 
 MeshMaterialList {
  5;
  31;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.511200;0.448800;0.473600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.740000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.367200;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.228800;0.228800;0.228800;0.450000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.119200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  45;
  -0.125958;0.860653;-0.493367;,
  -0.079987;0.566369;-0.820261;,
  -0.302321;0.790986;-0.531925;,
  -0.113338;0.585164;-0.802955;,
  -0.094125;0.243800;-0.965247;,
  -0.438778;0.459844;-0.772021;,
  -0.272719;0.360622;-0.891951;,
  -0.096050;0.099728;-0.990368;,
  -0.483425;0.206926;-0.850577;,
  -0.296074;0.156795;-0.942208;,
  -0.095918;0.044476;-0.994395;,
  -0.491751;0.097817;-0.865224;,
  -0.300529;0.072767;-0.950993;,
  -0.008839;-0.999940;-0.006449;,
  -0.004008;-0.999846;-0.017092;,
  -0.125193;-0.861304;-0.492424;,
  -0.034334;-0.570130;-0.820837;,
  -0.010628;-0.999843;-0.014147;,
  -0.012415;-0.999684;-0.021844;,
  -0.005652;-0.999935;-0.009944;,
  -0.182867;-0.928997;-0.321751;,
  -0.062883;-0.761710;-0.644859;,
  -0.002364;-0.999703;-0.024239;,
  0.999840;-0.017698;0.002577;,
  0.998772;-0.031929;0.037892;,
  0.989035;0.028319;0.144942;,
  -0.000309;0.001489;0.999999;,
  -0.000125;0.000938;1.000000;,
  -0.000878;0.000175;1.000000;,
  0.993498;0.052170;0.101195;,
  0.998449;0.032982;0.044850;,
  0.006866;0.015312;0.999859;,
  0.009822;0.009826;0.999904;,
  -0.164927;-0.770569;-0.615648;,
  -0.247081;-0.866003;-0.434730;,
  -0.074759;-0.637696;-0.766652;,
  0.999250;-0.038508;0.004169;,
  0.995254;0.022340;0.094712;,
  0.005206;-0.002538;0.999983;,
  -0.001894;-0.014958;0.999886;,
  0.230892;-0.006536;-0.972957;,
  0.999993;-0.002897;0.002447;,
  0.998271;-0.040435;-0.042667;,
  -0.007405;-0.015609;0.999851;,
  -0.001200;0.006031;0.999981;;
  31;
  3;0,3,2;,
  3;0,1,3;,
  4;2,3,6,5;,
  4;3,1,4,6;,
  4;5,6,9,8;,
  4;6,4,7,9;,
  4;8,9,12,11;,
  4;9,7,10,12;,
  3;17,17,18;,
  3;17,13,17;,
  3;14,14,19;,
  3;15,15,20;,
  3;21,15,15;,
  3;22,14,14;,
  3;23,24,25;,
  3;26,27,28;,
  3;29,30,23;,
  3;31,32,27;,
  3;30,24,23;,
  3;26,31,27;,
  3;33,16,34;,
  3;35,16,33;,
  3;36,37,29;,
  3;38,39,32;,
  3;37,30,29;,
  3;31,38,32;,
  3;40,16,3;,
  3;41,42,36;,
  3;43,44,39;,
  3;42,37,36;,
  3;38,43,39;;
 }
 MeshTextureCoords {
  31;
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.875000;0.375000;,
  0.750000;0.375000;,
  1.000000;0.375000;,
  0.875000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
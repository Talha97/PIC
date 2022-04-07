/*
  Date:03.05.2021
  AUTHOR:TALHA SEVINC

*/

#define clockCycle 1//150000
#define numberRound 10

const int8 GeneralKey[4][44] =
{ 
 { 0x54, 0x41, 0x49, 0x52, 0xd6, 0x97, 0xde, 0x8c, 0xcc, 0x5b, 0x85, 0x9, 0xd, 0x56, 0xd3, 0xda, 0x8e, 0xd8, 0xb, 0xd1, 0x3f, 0xe7, 0xec, 0x3d, 0xd6, 0x31, 0xdd, 0xe0, 0xe2, 0xd3, 0xe, 0xee, 0x4b, 0x98, 0x96, 0x78, 0x2f, 0xb7, 0x21, 0x59, 0xf3, 0x44, 0x65, 0x3c},
 { 0x41, 0x53, 0x4e, 0x41, 0x68, 0x3b, 0x75, 0x34, 0x7d, 0x46, 0x33, 0x7, 0xbc, 0xfa, 0xc9, 0xce, 0xc, 0xf6, 0x3f, 0xf1, 0x2a, 0xdc, 0xe3, 0x12, 0xe7, 0x3b, 0xd8, 0xca, 0x65, 0x5e, 0x86, 0x4c, 0xff, 0xa1, 0x27, 0x6b, 0x56, 0xf7, 0xd0, 0xbb, 0x4c, 0xbb, 0x6b, 0xd0},
 { 0x4c, 0x45, 0x43, 0x4c, 0x65, 0x20, 0x63, 0x2f, 0xb1, 0x91, 0xf2, 0xdd, 0x42, 0xd3, 0x21, 0xfc, 0x2d, 0xfe, 0xdf, 0x23, 0x82, 0x7c, 0xa3, 0x80, 0x4e, 0x32, 0x91, 0x11, 0x85, 0xb7, 0x26, 0x37, 0x11, 0xa6, 0x80, 0xb7, 0xd2, 0x74, 0xf4, 0x43, 0xc6, 0xb2, 0x46, 0x5},
 { 0x48, 0x56, 0x4b, 0x4c, 0x48, 0x1e, 0x55, 0x19, 0x2c, 0x32, 0x67, 0x7e, 0x2d, 0x1f, 0x78, 0x6, 0x7a, 0x65, 0x1d, 0x1b, 0x44, 0x21, 0x3c, 0x27, 0x63, 0x42, 0x7e, 0x59, 0x82, 0xc0, 0xbe, 0xe7, 0xaa, 0x6a, 0xd4, 0x33, 0x16, 0x7c, 0xa8, 0x9b, 0xdd, 0xa1, 0x9, 0x92}
};



int8 Key[4][4] = { {  0x54,0x41,0x49,0x52  },{  0x41,0x53,0x4E,0x41  },{ 0x4C,0x45,0x43,0x4C }, { 0x48,0x56,0x4B,0x4C } };
const int8 Rcon[11] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 }; 


int KeyCounter = 0;

int8 tempArray[4];
int8 message[16]    ;
int8 CryptedData[16];
int8 stateMatrix[4][4];

int8 reverseStateMatrix[4][4];
int8 DecryptedData[16];

void convertDataToState();
void AESEncrypt(int8 *arrayS,int arraySize,int8 *destinationArray);
void Subbytes(void);
void ShiftRows(void);
void MixColumns(void);
void mixSubCol(int section);
void AddRoundKey(int selection);
void KeyExtension(void);
void GFunction(int8 *lastWord, int selection);
void convertStateToData();


void ConvReverseToData();
void miniReverseMix(int section);
void ReverseShift();
void ReverseSubBytes();
void ReverseMixColumns();
void AESDecrypte(int8 *cryptedDatas,int16 arraySize,int8 *destinationArray);
void ConvertDataToReverseArray(int8 *arrayNew);


int8 mul14(int8 a);
int8 mul13(int8 a);
int8 mul11(int8 a);
int8 mult9(int8 a);
int8 mul2 (int8 a);
int8 mul3 (int8 a);
void clear();

int counter=0;
int8 rawData[16];

void clear()
{
   int i=0;
   for ( i = 0; i < 16; i++) message[i] = 0;
   for ( i = 0; i < 16; i++) rawData[i] = 0;   
}

int8 mul2(int8 a)
{
   if (a > 255) a = a & 0x0FF;
   int1 control = a >> 7;
   a = a << 1;
   a = a & 0x0FF;
   if (control)  a = a ^ 0x1B;
   return a;

}

int8 mul3(int8 a)
{
   return mul2(a) ^ a;
}



int8 mul14(int a)
{
   int temp = a;
   temp = mul2(temp);
   temp ^= a;
   temp = mul2(temp);
   temp ^= a;
   temp = mul2(temp);
   return temp;

}

int8 mul13(int a)
{
   int temp = a;
   temp = mul2(temp);
   temp ^= a;
   for (int i = 0; i < 2; i++) temp = mul2(temp);
   temp ^= a;
   return temp;

}


int8 mul11(int8 a)
{
   int temp = a;
   for (int i = 0; i < 2; i++) temp = mul2(temp);
   temp ^= a;
   temp = mul2(temp);
   temp ^= a;
   return temp;


}

int8 mult9(int8 a)
{
   int temp = a;
   for (int i = 0; i < 3; i++)   temp = mul2(temp);
   temp = a ^ temp;
   return temp;
   

}




void convertDataToState()
{
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
      {
         stateMatrix[i][j] = rawData[4 * j + i];
         for(int32 i=0;i<clockCycle;i++);
         
      }
}

void convertStateToData()
{
   int count = 0;
   for (int i = 0; i < 4; i++)
   {   for (int j = 0; j < 4; j++)
      {
         CryptedData[count] = stateMatrix[j][i];
         count++;
        
      }
   }
}

void Subbytes(void)
{
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {   
         
         stateMatrix[i][j] = SBOX[ stateMatrix[i][j] >>4 ][stateMatrix[i][j] & 0x0F]; //SBOX[ level ]*(SBOX+level); 

      }
   }
}
void ShiftRows()
{
   int temp  = 0;
   int temp2 = 0;

   temp = stateMatrix[1][0];
   stateMatrix[1][0]= stateMatrix[1][1];
   stateMatrix[1][1] = stateMatrix[1][2];
   stateMatrix[1][2] = stateMatrix[1][3];
   stateMatrix[1][3] = temp;
   
   temp = stateMatrix[2][0];
   temp2 = stateMatrix[2][1];
   stateMatrix[2][0] = stateMatrix[2][2];
   stateMatrix[2][1] = stateMatrix[2][3];
   stateMatrix[2][2] = temp;
   stateMatrix[2][3] = temp2;

   temp = stateMatrix[3][3];
   stateMatrix[3][3] = stateMatrix[3][2];
   stateMatrix[3][2] = stateMatrix[3][1];
   stateMatrix[3][1] = stateMatrix[3][0];
   stateMatrix[3][0] = temp;
}



void mixSubCol(int section)
{
   
   int1 mul2control = 0;
   int1 mul3control = 0;
   int temp0, temp1, temp2, temp3;
   int trans0, trans1, trans2, trans3;
   int tempArray[4];

   for (int i = 0; i < 4;i++) 
   {
      tempArray[i] = stateMatrix[i][section - 1];
      for(int32 i=0;i<clockCycle;i++);
   
   }
   
   /*Ilk dongu.*/
   
   mul2control = (tempArray[0] >> 7);
   mul3control = (tempArray[1] >> 7);
   trans0=tempArray[0] << 1;   
   if (mul2control) trans0 ^= 0x1B;
   trans0 &= 0xFF;
   trans1 = tempArray[1] << 1;
   if (mul3control) trans1 ^= 0x1B;
   trans1 ^= tempArray[1];
   trans1 &= 0xFF;

   temp0 = trans0 ^ trans1^tempArray[2] ^ tempArray[3];
   
   /*Ikinci dongu.*/

   mul2control = (tempArray[1] >> 7);
   mul3control = (tempArray[2] >> 7);
   trans0 = tempArray[1] << 1;
   if (mul2control) trans0 ^= 0x1B;
   trans0 &= 0xFF;
   trans1 = tempArray[2] << 1;
   if (mul3control) trans1 ^= 0x1B;
   trans1 ^= tempArray[2];
   trans1 &= 0xFF;

   temp1 = trans0 ^ trans1 ^ tempArray[0] ^ tempArray[3];

   /*Ucuncu dongu.*/

   mul2control = (tempArray[2] >> 7);
   mul3control = (tempArray[3] >> 7);
   trans0 = tempArray[2] << 1;
   if (mul2control) trans0 ^= 0x1B;
   trans0 &= 0xFF;
   trans1 = tempArray[3] << 1;
   if (mul3control) trans1 ^= 0x1B;
   trans1 ^= tempArray[3];
   trans1 &= 0xFF;
   temp2 = trans0 ^ trans1^tempArray[0] ^ tempArray[1];

   /*Dorduncu dongu.*/

   mul2control = (tempArray[3] >> 7);
   mul3control = (tempArray[0] >> 7);
   trans0 = tempArray[3] << 1;
   if (mul2control) trans0 ^= 0x1B;
   trans0 &=0xFF;
   trans1 = tempArray[0] << 1;
   if (mul3control) trans1 ^= 0x1B;
   trans1 ^= tempArray[0];
   trans1 &= 0xFF;
   temp3 = trans0 ^ trans1^tempArray[1] ^ tempArray[2];

   stateMatrix[0][section - 1] = temp0;
   stateMatrix[1][section - 1] = temp1;
   stateMatrix[2][section - 1] = temp2;
   stateMatrix[3][section - 1] = temp3;


}


void MixColumns()
{
   for (int i = 1; i < 5;i++) mixSubCol(i);
}

void AddRoundKey(int selection)
{
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         stateMatrix[i][j] = stateMatrix[i][j] ^ GeneralKey[i][4 * selection + j];
         for(int32 i=0;i<clockCycle;i++);
      }
   }
}

void AESEncrypt(int8 *arrayS, int arraySize,int8 *destinationArray)
{
   
   int i,j=0;
   
   int division = arraySize / 16;
   int remining = arraySize % 16;
   for ( i = 0; i <= division; i++)
   {
      if ((i == division && remining == 0)) 
         break;

      if (i != division || (i==division && remining==0))
      {
         for ( j = 0; j < 16; j++)         rawData[j] = arrayS[i*16+j];
      }

      else if(remining!=0)
      {
         for ( j = 0; j < remining; j++)            rawData[j] = arrayS[i * 16 + j];
         for ( j = (remining + 1); j < 16; j++)     rawData[j] = 0;
      }
      
    
      
      convertDataToState();
      AddRoundKey(0);

      for ( i = 0; i < 9; i++)
      {

         Subbytes();  
 
         ShiftRows(); 

         MixColumns(); 
         
         AddRoundKey(i + 1);
         
       
      }


      Subbytes();
      
      ShiftRows();
      
      AddRoundKey(10);
      
      convertStateToData();
      
      counter=0;
      
      for(int cryptedCount=0; cryptedCount<16; cryptedCount++)
         destinationArray[16*i+cryptedCount]=CryptedData[cryptedCount];

           
   }
}


void ConvertDataToReverseArray(int8 *arrayNew)
{

    for(int i=0;i<4;i++)
    {    for (int j = 0; j < 4; j++)
        {
          reverseStateMatrix[i][j] = arrayNew[4*j+i];          

        }
    }
}

void ConvReverseToData()
{
   int count = 0;
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      { 
         DecryptedData[count] = reverseStateMatrix[j][i]; 
         count++; 
      }
   }

}


void InvAddRoundKey(int selection)
{
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         reverseStateMatrix[i][j] = reverseStateMatrix[i][j] ^ GeneralKey[i][4 * selection + j];
      }
   }
}


void ReverseShift()
{
   int temp,temp2;

   temp = reverseStateMatrix[1][3];
   reverseStateMatrix[1][3] = reverseStateMatrix[1][2];
   reverseStateMatrix[1][2] = reverseStateMatrix[1][1];
   reverseStateMatrix[1][1] = reverseStateMatrix[1][0];
   reverseStateMatrix[1][0] = temp;

   temp  = reverseStateMatrix[2][2];
   temp2 = reverseStateMatrix[2][3];
   reverseStateMatrix[2][3] = reverseStateMatrix[2][1];
   reverseStateMatrix[2][2] = reverseStateMatrix[2][0];
   reverseStateMatrix[2][1] = temp2;
   reverseStateMatrix[2][0] = temp;

   temp = reverseStateMatrix[3][0];
   reverseStateMatrix[3][0] = reverseStateMatrix[3][1];
   reverseStateMatrix[3][1] = reverseStateMatrix[3][2];
   reverseStateMatrix[3][2] = reverseStateMatrix[3][3];
   reverseStateMatrix[3][3] = temp;    

}

void ReverseSubBytes()
{
   
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         reverseStateMatrix[i][j] = INV_SBOX[ reverseStateMatrix[i][j] >> 4 ][ reverseStateMatrix[i][j] & 0x0F ];
      }
   }

}



void miniReverseMix(int section)
{

   int trans0, trans1, trans2, trans3;
   int temp[4];

   for (int i = 0; i < 4; i++) temp[i] = reverseStateMatrix[i][section - 1];

   trans0 = mul14(temp[0]) ^ mul11(temp[1]) ^ mul13(temp[2]) ^ mult9(temp[3]);
   trans1 = mult9(temp[0]) ^ mul14(temp[1]) ^ mul11(temp[2]) ^ mul13(temp[3]);
   trans2 = mul13(temp[0]) ^ mult9(temp[1]) ^ mul14(temp[2]) ^ mul11(temp[3]);
   trans3 = mul11(temp[0]) ^ mul13(temp[1]) ^ mult9(temp[2]) ^ mul14(temp[3]);

   reverseStateMatrix[0][section - 1] = trans0;
   reverseStateMatrix[1][section - 1] = trans1;
   reverseStateMatrix[2][section - 1] = trans2;
   reverseStateMatrix[3][section - 1] = trans3;

}


void ReverseMixColumns()
{
   for (int i = 0; i < 4; i++) 
   { miniReverseMix(i + 1); }
   
}


void AESDecrypte(int8 *cryptedDatas,int16 arraySize,int8 *destinationArray)
{
   
   int division = arraySize / 16;
   int remining = arraySize % 16;
   int8 transientArray[16];
   
   for(int k=0;k<=division;k++)
   {
      for(int l=0;l<16;l++)
         transientArray[l]=cryptedDatas[16*k+l];
 
      ConvertDataToReverseArray(transientArray);
      InvAddRoundKey(numberRound);
   
      for (int i = (numberRound-1) ; i > 0; i--)
      {
         ReverseShift();   
         ReverseSubBytes();
         InvAddRoundKey(i);
         ReverseMixColumns();
   
      }
   
      ReverseShift();
      ReverseSubBytes();
      InvAddRoundKey(0);
      ConvReverseToData();
      
      for(int j=0;j<16;j++)
        destinationArray[16*k+j]=decryptedData[j];
   }
}


void GFunction(int8 *lastWord, int selection)
{
   int temp = lastWord[0];
   tempArray[0] = lastWord[1];
   tempArray[1] = lastWord[2];
   tempArray[2] = lastWord[3];
   tempArray[3] = temp;

   tempArray[0] = SBOX[tempArray[0]];
   tempArray[1] = SBOX[tempArray[1]];
   tempArray[2] = SBOX[tempArray[2]];
   tempArray[3] = SBOX[tempArray[3]];

   tempArray[0] = tempArray[0] ^ Rcon[selection];
   tempArray[1] ^= 0x00;
   tempArray[2] ^= 0x00;
   tempArray[3] ^= 0x00;


}


void KeyExtension()
{
   int tempArray2[4];
   int tempArray3[4];
   int i,a=0;
   for ( i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         GeneralKey[i][j] = Key[i][j];

   int select = 3;
   for ( i = 4; i < 4 * numberRound + 4; i++)
   {
      if (i % 4 == 0)
      {
         for ( a = 0; a < 4; a++) tempArray2[a] = GeneralKey[a][select];
         for ( a = 0; a < 4; a++) tempArray3[a] = GeneralKey[a][select - 3];
         GFunction(tempArray2, KeyCounter);
         for ( a = 0; a < 4; a++) 
            GeneralKey[a][select + 1] = tempArray[a] ^ tempArray3[a];
         select += 4;
         KeyCounter++;
      }

      else
      {
         for ( a = 0; a < 4; a++) GeneralKey[a][i] = GeneralKey[a][i - 1] ^ GeneralKey[a][i - 4];

      }
   }

}



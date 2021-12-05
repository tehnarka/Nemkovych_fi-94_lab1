#include <iostream>
#include "main.h"

using namespace std;

void EXPECT_EQ(const LongNum& A, const LongNum& B, string TestName)
{
    cout << "TEST " << TestName << endl;
    if (A.LongCmp(B) == 0)
    {
        cout << "[ OK ] A equal B " << endl;
    }
    else
    {
        cout << "[ ERROR ] A not equal B " << endl;
    }
}

void EXPECT_EQ(string A, string B, string TestName)
{
    cout << "TEST " << TestName << endl;
    if (A == B)
    {
        cout << "[ OK ] A equal B " << endl;
    }
    else
    {
        cout << "[ ERROR ] A not equal B " << endl;
    }
}



void LongSumTest() {

    LongNum second_mult("1");

    LongNum num("2");


    LongNum comparison("3");


    num = num.LongAdd(second_mult);



    EXPECT_EQ(num, comparison, "LongSumTest");
}

void LongMulTest() {

    LongNum second_mult("FF");

    LongNum num("2");


    LongNum comparison("1FE");


    num = num.LongMul(second_mult);



    EXPECT_EQ(num, comparison, "LongMulTest1");
}

void LongMultiplicationTest() {

    LongNum second_mult("FFF");

    LongNum num("FFF23F");


    LongNum comparison("0");

    for (/*LongNum i( "0" ); i.LongCmp( second_mult ) == -1; i = i.LongAdd( LongNum( "1" ) )*/ size_t i = 0; i < 4095; ++i)
    {
        comparison = comparison.LongAdd(num);
    }

    num = num.LongMul(second_mult);

    LongNum result("FFE23FDC1");

    EXPECT_EQ(num, result, "LongMultiplicationTest");
    EXPECT_EQ(result, comparison, "LongMultiplicationTest");
    EXPECT_EQ(num, comparison, "LongMultiplicationTest");
}

void LongPowerTest() {

    LongNum second_mult("FA");

    LongNum num("FF");

    num = num.LongPower(second_mult);

    LongNum comparison("6039EE32CBE6CA66F3241C7EEDCB5576A935151D41EA74CC4115DF10A1234FEC4235390D5FC6D106F21E28B76A0F1ED5071A5D98D67F5001DA2201218743F9DA6B09E1BC0694060172E1F637F7FA84E5AC315E37E0C5501CFE5C1112B75AE2C7580A21C33A209AD0EB5154E9B3D233C2591517BB4E1434FB18CFE312FBF37A0BAE2AFEF666B126D6D316F76867A495C4EEDF4A911893F80FE0113214357FD2EE3818CE23106210F1C4925693D0232183686EE4CEFCBA0E3AAFEBCA40875984A551DE362F8BC4B571290C3223557AFD4B6C1508B5BFBC5ADDD086BB436ADAED3B3478DF4FCE3E8244323254ABF928E37B4ED32917B07BB1940601");

    EXPECT_EQ(num, comparison, "LongPowerTest");
}

void LongDifTest() {

    LongNum a("abc4562397123cdceffffffeeeaaacccc27799554c54a6a6a5adbd");

    LongNum b("abc4564562397123cdcefff456fffeeeaaacccc27794569554c54a6a6a5adbd");


    LongNum c("abc45645577d2bc1945ddc2687fffeeebbc221f5ab6cdd00000000000000000");

    EXPECT_EQ(b.LongSub(a), c, "LongDifTest");
}

void LongPowerTest2() {

    LongNum second_mult("F");

    LongNum num("FFF23F");


    LongNum comparison("FF31FE84CA7B5C732B719F258A7D4569A9A51F2E1BB2D0F2A57B6F58A3D0333D3A1F06F79CCDAD3FED262FA1BF");

    num = num.LongPower(second_mult);

    EXPECT_EQ(num, comparison, "LongPowerTest2");
}

void LongModTest1() {

    LongNum a("FFFFFFF");

    LongNum b("FF");

    LongNum c("F");

    EXPECT_EQ(a.LongMod(b), c, "LongModTest1");
}


void LongDivTest1() {

    LongNum a("FFFFFFF");

    LongNum b("FF");

    LongNum c("101010");

    EXPECT_EQ(a.LongDiv(b), c, "LongDivTest1");
}

void LongDivTest11() {

    LongNum a("FFFFFFF");

    LongNum b("FFF");

    LongNum c("10010");

    EXPECT_EQ(a.LongDiv(b), c, "LongDivTest11");

    EXPECT_EQ((a.LongMul(b)).LongDiv(b), a, "LongDivTest11");
}

void LongDivTest2() {

    LongNum a("D4D2110984907B5625309D956521BAB4157B8B1ECE04043249A3D379AC112E5B9AF44E721E148D88A942744CF56A06B92D28A0DB950FE4CED2B41A0BD38BCE7D0BE1055CF5DE38F2A588C2C9A79A75011058C320A7B661C6CE1C36C7D870758307E5D2CF07D9B6E8D529779B6B2910DD17B6766A7EFEE215A98CAC300F2827DB");

    LongNum b("3A7EF2554E8940FA9B93B2A5E822CC7BB262F4A14159E4318CAE3ABF5AEB1022EC6D01DEFAB48B528868679D649B445A753684C13F6C3ADBAB059D635A2882090FC166EA9F0AAACD16A062149E4A0952F7FAAB14A0E9D3CB0BE9200DBD3B0342496421826919148E617AF1DB66978B1FCD28F8408506B79979CCBCC7F7E5FDE7");

    EXPECT_EQ(((a.LongMul(b)).LongDiv(b)), a, "LongDivTest2");
}

void HexOutTest() {

    LongNum a("abc4562397123cdceffffffeeeaaacccc27799554c54a6a6a5adbd");

    std::string hex = a.GetHex();

    EXPECT_EQ(hex, "abc4562397123cdceffffffeeeaaacccc27799554c54a6a6a5adbd", "HexOutTest");
}

void GCDTest()
{
    LongNum a("d4d2110984907b5625309d956521bab4157b8b1ece04043249a3d379ac112e5b9af44e721e148d88a942744cf56a06b92d28a0db950fe4ced2b41a0bd38bce7d0be1055cf5de38f2a588c2c9a79a75011058c320a7b661c6ce1c36c7d870758307e5d2cf07d9b6e8d529779b6b2910dd17b6766a7efee215a98cac300f2827db");

    LongNum b("3a7ef2554e8940fa9b93b2a5e822cc7bb262f4a14159e4318cae3abf5aeb1022ec6d01defab48b528868679d649b445a753684c13f6c3adbab059d635a2882090fc166ea9f0aaacd16a062149e4a0952f7faab14a0e9d3cb0be9200dbd3b0342496421826919148e617af1db66978b1fcd28f8408506b79979ccbcc7f7e5fde7");

    LongNum result("1");

    EXPECT_EQ(a.GCD(b), result, "GCD_Test");
}

void LCMTest()
{
    LongNum a("d4d2110984907b5625309d956521bab4157b8b1ece04043249a3d379ac112e5b9af44e721e148d88a942744cf56a06b92d28a0db950fe4ced2b41a0bd38bce7d0be1055cf5de38f2a588c2c9a79a75011058c320a7b661c6ce1c36c7d870758307e5d2cf07d9b6e8d529779b6b2910dd17b6766a7efee215a98cac300f2827db");

    LongNum b("3a7ef2554e8940fa9b93b2a5e822cc7bb262f4a14159e4318cae3abf5aeb1022ec6d01defab48b528868679d649b445a753684c13f6c3adbab059d635a2882090fc166ea9f0aaacd16a062149e4a0952f7faab14a0e9d3cb0be9200dbd3b0342496421826919148e617af1db66978b1fcd28f8408506b79979ccbcc7f7e5fde7");

    LongNum result("30a120b609dcbe28b09ca92e12dd29d77ae6400dc22b026afb5fb945aaf62b57f4e48bd299261f02bbb35dd2495b5cd2713bf0e30192dae1b334659160c8552423f0ad7fb82870920df4e9b57980ead2ada9f3ef4b5d0718ab7f1053700395278998cb9ad48498d65150e3e837b0bb169d432b441424557061f838a17c65f90a31105f599bf69b87485bf9c70f51d37a417e476e372558c26782ac8c8f35c3d1227e851d8a72cd708700fd90c5e17f22c4ea15730345e56bd76f04b54580813cbe306b4404c6f34bcd9840d2911e6b3cf6de3ee428c274edf0a97335d8256da26fcd67ba5450593a15f6b527ece76fbbe20f7a882347614af4b7faf55086659d");

    EXPECT_EQ(a.LCM(b), result, "LCM_Test");
}


void LongAddModTest()
{
    LongNum a("d4d2110984907b5625309d956521bab4157b8b1ece04043249a3d379ac112e5b9af44e721e148d88a942744cf56a06b92d28a0db950fe4ced2b41a0bd38bce7d0be1055cf5de38f2a588c2c9a79a75011058c320a7b661c6ce1c36c7d870758307e5d2cf07d9b6e8d529779b6b2910dd17b6766a7efee215a98cac300f2827db");

    LongNum b("3a7ef2554e8940fa9b93b2a5e822cc7bb262f4a14159e4318cae3abf5aeb1022ec6d01defab48b528868679d649b445a753684c13f6c3adbab059d635a2882090fc166ea9f0aaacd16a062149e4a0952f7faab14a0e9d3cb0be9200dbd3b0342496421826919148e617af1db66978b1fcd28f8408506b79979ccbcc7f7e5fde7");

    LongNum n("269d7722ea018f2ac35c5a3517aa06eaa1949059ae8240428bbfd0a8be6e2ebf91223991f80d7413d6b2eb213e7122710edec617460fa0191f3901604619972018ebef22d81aed9c56424014cadcc2ccdee67d36a54bfc500230ca6693aba057b374746622341ed6d52fe5a79e6860f54f197791b3fef49fd534cb2c675b6bdb");

    LongNum result("102c16a6d0ed225693dd8c7a79e56c55cce8d4c49ce26920413599bd1f8f7418f71bd53506aec5052c66e01a4ed59fc3a47baf9ea0ebefaa32aadcd43012ea56d2ee253ac2c64796059644cb9db2ab9f00601b6c38c4f61caafce078bfa165f691ac5868185f397625521e17ce5f547bb2d29af180ce9504ee7dac1338e32c5");

    EXPECT_EQ(a.LongAddMod(b, n), result, "LongAddModTest");
}

void LongSubModTest()
{
    LongNum a("d4d2110984907b5625309d956521bab4157b8b1ece04043249a3d379ac112e5b9af44e721e148d88a942744cf56a06b92d28a0db950fe4ced2b41a0bd38bce7d0be1055cf5de38f2a588c2c9a79a75011058c320a7b661c6ce1c36c7d870758307e5d2cf07d9b6e8d529779b6b2910dd17b6766a7efee215a98cac300f2827db");

    LongNum b("3a7ef2554e8940fa9b93b2a5e822cc7bb262f4a14159e4318cae3abf5aeb1022ec6d01defab48b528868679d649b445a753684c13f6c3adbab059d635a2882090fc166ea9f0aaacd16a062149e4a0952f7faab14a0e9d3cb0be9200dbd3b0342496421826919148e617af1db66978b1fcd28f8408506b79979ccbcc7f7e5fde7");

    LongNum n("269d7722ea018f2ac35c5a3517aa06eaa1949059ae8240428bbfd0a8be6e2ebf91223991f80d7413d6b2eb213e7122710edec617460fa0191f3901604619972018ebef22d81aed9c56424014cadcc2ccdee67d36a54bfc500230ca6693aba057b374746622341ed6d52fe5a79e6860f54f197791b3fef49fd534cb2c675b6bdb");

    LongNum result("267ab94b78028cdb3f87dc503600d9787e5ae57081235f3919b626c015db91f9fb209fdd3b37a5fa9cc14b4bd57b5b0b8b55c9d48374c9a7ca037887a7168713b15bd109ce82c5508c21a076a8ba23477baaa06816e8990bbba0b78660329139a424541a382445d5f41ed4c9295862dd5d411774ddfb4c9cb0218de2e12fe663");

    EXPECT_EQ(a.LongSubMod(b, n), result, "LongSubModTest");
}


void LongMulModTest_Easy()
{
    LongNum a("FFF");

    LongNum b("AAA");

    LongNum n("AAAF");

    LongNum result("9105");

    EXPECT_EQ(a.LongMulMod(b, n), result, "LongMulModTest_Easy");
}

void LongPowModTest_Easy()
{
    LongNum a("FFF");

    LongNum b("AAA");

    LongNum n("AAAF");

    LongNum result("63D8");

    EXPECT_EQ(a.LongModPowerBarrett(b, n), result, "LongPowModTest_Easy");
}

void LongMulModTest()
{
    LongNum a("d4d2110984907b5625309d956521bab4157b8b1ece04043249a3d379ac112e5b9af44e721e148d88a942744cf56a06b92d28a0db950fe4ced2b41a0bd38bce7d0be1055cf5de38f2a588c2c9a79a75011058c320a7b661c6ce1c36c7d870758307e5d2cf07d9b6e8d529779b6b2910dd17b6766a7efee215a98cac300f2827db");

    LongNum b("3a7ef2554e8940fa9b93b2a5e822cc7bb262f4a14159e4318cae3abf5aeb1022ec6d01defab48b528868679d649b445a753684c13f6c3adbab059d635a2882090fc166ea9f0aaacd16a062149e4a0952f7faab14a0e9d3cb0be9200dbd3b0342496421826919148e617af1db66978b1fcd28f8408506b79979ccbcc7f7e5fde7");

    LongNum n("269d7722ea018f2ac35c5a3517aa06eaa1949059ae8240428bbfd0a8be6e2ebf91223991f80d7413d6b2eb213e7122710edec617460fa0191f3901604619972018ebef22d81aed9c56424014cadcc2ccdee67d36a54bfc500230ca6693aba057b374746622341ed6d52fe5a79e6860f54f197791b3fef49fd534cb2c675b6bdb");

    LongNum result("b274d0d82e9b2997834fe06626976c55d7bad04a38623214d2c29f08d4bb6d4c3eb31d0bf3b5bb7965f820af3ceb31fd0498d6e94feab692c36df783c400d19a0f1a25e9232945024c249770c34f610d9dd31672b1cfbde78856afe52cb54ca3750fb6d4529c0b4e491c12aebb0f2db2f8449107611cc66cac56b4275c31ee7");

    EXPECT_EQ(a.LongMulMod(b, n), result, "LongMulModTest");
}

void LongPowModTest()
{
    LongNum a("d4d2110984907b5625309d956521bab4157b8b1ece04043249a3d379ac112e5b9af44e721e148d88a942744cf56a06b92d28a0db950fe4ced2b41a0bd38bce7d0be1055cf5de38f2a588c2c9a79a75011058c320a7b661c6ce1c36c7d870758307e5d2cf07d9b6e8d529779b6b2910dd17b6766a7efee215a98cac300f2827db");

    LongNum b("3a7ef2554e8940fa9b93b2a5e822cc7bb262f4a14159e4318cae3abf5aeb1022ec6d01defab48b528868679d649b445a753684c13f6c3adbab059d635a2882090fc166ea9f0aaacd16a062149e4a0952f7faab14a0e9d3cb0be9200dbd3b0342496421826919148e617af1db66978b1fcd28f8408506b79979ccbcc7f7e5fde7");

    LongNum n("269d7722ea018f2ac35c5a3517aa06eaa1949059ae8240428bbfd0a8be6e2ebf91223991f80d7413d6b2eb213e7122710edec617460fa0191f3901604619972018ebef22d81aed9c56424014cadcc2ccdee67d36a54bfc500230ca6693aba057b374746622341ed6d52fe5a79e6860f54f197791b3fef49fd534cb2c675b6bdb");

    LongNum result("11e97d13ac2368a6ddcc2a87b5c71cd0b33951d68ef905f95a7efa2bf49ebeec63bfdd69c6022e93d0963407b8a0942a72c6cafbccfc66c3ed2bbe86751b41e7d69e23a430794e9edd055b5741ad83bda475af10fed1b331cb4287280d51a518a3940c24c336f789cd8035d4156a29e15a88ede96e0ef32cd1be12ea034fece1");

    EXPECT_EQ(a.LongModPowerBarrett(b, n), result, "LongPowModTest");
}


int main()
{
    LongMulTest();
    LongSumTest();
    LongMultiplicationTest();
    LongPowerTest();
    LongPowerTest2();
    LongDifTest();
    LongDivTest1();
    LongDivTest2();
    LongModTest1();
    HexOutTest();
    GCDTest();
    LCMTest();
    LongAddModTest();
    LongSubModTest();
    LongMulModTest_Easy();
    LongPowModTest_Easy();
    LongMulModTest();
    LongPowModTest();
    return 0;
}
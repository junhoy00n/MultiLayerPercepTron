#include <iostream>
#include <math.h>

using namespace std;

#define outputNodeCnt 10 // 출력층 노트 갯수
#define hiddenNodeCnt 24 // 은닉층 노드 갯수
#define inputNodeCnt 25 // 입력층 노드 갯수

double weight = 0.7; // 가중치
double eta = 0.1; // eta 값
double offset = 0.1; // offset 값
int epoch = 0; // epoch 학습 모델 가중치 수정 싸이클 횟수 계산
double tmp, sum;

int main() {
   int AstudyPattern[inputNodeCnt] = {1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; // AstudyPattern 학습 패턴
   int Apoint[outputNodeCnt] = { 1,0,0,0,0,0,0,0,0,0 }; // AstudyPattern 교사 신호
   double AHidToOut[hiddenNodeCnt], // AstudyPattern 은닉층 -> 출력층 출력 값
      Aresult[outputNodeCnt], // AstudyPattern 교사 신호 결과
      AoutputDelta[outputNodeCnt], // AstudyPattern 출력층 오차 계산
      AhiddenDelta[hiddenNodeCnt], // AstudyPattern 은닉층 오차 계산
      AHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // AstudyPattern 은닉층 -> 출력층 가중치
      AInToHidWeight[hiddenNodeCnt][inputNodeCnt], // AstudyPattern 입력층 -> 은닉층 가중치
      AHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // AstudyPattern 가중치 변화량
      AInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // AstudyPattern 가중치 변화량


   int BstudyPattern[inputNodeCnt] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1}; // BstudyPattern 학습 패턴
   int Bpoint[outputNodeCnt] = { 0,1,0,0,0,0,0,0,0,0 }; // BstudyPattern 교사 신호
   double BHidToOut[hiddenNodeCnt], // BstudyPattern 은닉층 -> 출력층 출력 값
      Bresult[outputNodeCnt], // BstudyPattern 교사 신호 결과
      BoutputDelta[outputNodeCnt], // BstudyPattern 출력층 오차 계산
      BhiddenDelta[hiddenNodeCnt], // BstudyPattern 은닉층 오차 계산
      BHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // BstudyPattern 은닉층 -> 출력층 가중치
      BInToHidWeight[hiddenNodeCnt][inputNodeCnt], // BstudyPattern 입력층 -> 은닉층 가중치
      BHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // BstudyPattern 가중치 변화량
      BInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // BstudyPattern 가중치 변화량


   int CstudyPattern[inputNodeCnt] = {1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1}; // CstudyPattern 학습 패턴
   int Cpoint[outputNodeCnt] = { 0,0,1,0,0,0,0,0,0,0 }; // CstudyPattern 교사 신호
   double CHidToOut[hiddenNodeCnt], // CstudyPattern 은닉층 -> 출력층 출력 값
      Cresult[outputNodeCnt], // CstudyPattern 교사 신호 결과
      CoutputDelta[outputNodeCnt], // CstudyPattern 출력층 오차 계산
      ChiddenDelta[hiddenNodeCnt], // CstudyPattern 은닉층 오차 계산
      CHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // CstudyPattern 은닉층 -> 출력층 가중치
      CInToHidWeight[hiddenNodeCnt][inputNodeCnt], // CstudyPattern 입력층 -> 은닉층 가중치
      CHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // CstudyPattern 가중치 변화량
      CInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // CstudyPattern 가중치 변화량
	
   int DstudyPattern[inputNodeCnt] = {1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1}; // DstudyPattern 학습 패턴
   int Dpoint[outputNodeCnt] = { 0,0,0,1,0,0,0,0,0,0 }; // DstudyPattern 교사 신호
   double DHidToOut[hiddenNodeCnt], // DstudyPattern 은닉층 -> 출력층 출력 값
      Dresult[outputNodeCnt], // DstudyPattern 교사 신호 결과
      DoutputDelta[outputNodeCnt], // DstudyPattern 출력층 오차 계산
      DhiddenDelta[hiddenNodeCnt], // DstudyPattern 은닉층 오차 계산
      DHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // DstudyPattern 은닉층 -> 출력층 가중치
      DInToHidWeight[hiddenNodeCnt][inputNodeCnt], // DstudyPattern 입력층 -> 은닉층 가중치
      DHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // DstudyPattern 가중치 변화량
      DInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // DstudyPattern 가중치 변화량
	
   int EstudyPattern[inputNodeCnt] = {0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,0,1}; // EstudyPattern 학습 패턴
   int Epoint[outputNodeCnt] = { 0,0,0,0,1,0,0,0,0,0 }; // EstudyPattern 교사 신호
   double EHidToOut[hiddenNodeCnt], // EstudyPattern 은닉층 -> 출력층 출력 값
      Eresult[outputNodeCnt], // EstudyPattern 교사 신호 결과
      EoutputDelta[outputNodeCnt], // EstudyPattern 출력층 오차 계산
      EhiddenDelta[hiddenNodeCnt], // EstudyPattern 은닉층 오차 계산
      EHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // EstudyPattern 은닉층 -> 출력층 가중치
      EInToHidWeight[hiddenNodeCnt][inputNodeCnt], // EstudyPattern 입력층 -> 은닉층 가중치
      EHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // EstudyPattern 가중치 변화량
      EInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // EstudyPattern 가중치 변화량
	
   int FstudyPattern[inputNodeCnt] = {0,1,1,1,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,0,1,1,1,0}; // FstudyPattern 학습 패턴
   int Fpoint[outputNodeCnt] = { 0,0,0,0,0,1,0,0,0,0 }; // FstudyPattern 교사 신호
   double FHidToOut[hiddenNodeCnt], // FstudyPattern 은닉층 -> 출력층 출력 값
      Fresult[outputNodeCnt], // FstudyPattern 교사 신호 결과
      FoutputDelta[outputNodeCnt], // FstudyPattern 출력층 오차 계산
      FhiddenDelta[hiddenNodeCnt], // FstudyPattern 은닉층 오차 계산
      FHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // FstudyPattern 은닉층 -> 출력층 가중치
      FInToHidWeight[hiddenNodeCnt][inputNodeCnt], // FstudyPattern 입력층 -> 은닉층 가중치
      FHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // FstudyPattern 가중치 변화량
      FInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // FstudyPattern 가중치 변화량
	
   int GstudyPattern[inputNodeCnt] = {0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1}; // GstudyPattern 학습 패턴
   int Gpoint[outputNodeCnt] = { 0,0,0,0,0,0,1,0,0,0 }; // GstudyPattern 교사 신호
   double GHidToOut[hiddenNodeCnt], // GstudyPattern 은닉층 -> 출력층 출력 값
      Gresult[outputNodeCnt], // GstudyPattern 교사 신호 결과
      GoutputDelta[outputNodeCnt], // GstudyPattern 출력층 오차 계산
      GhiddenDelta[hiddenNodeCnt], // GstudyPattern 은닉층 오차 계산
      GHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // GstudyPattern 은닉층 -> 출력층 가중치
      GInToHidWeight[hiddenNodeCnt][inputNodeCnt], // GstudyPattern 입력층 -> 은닉층 가중치
      GHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // GstudyPattern 가중치 변화량
      GInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // GstudyPattern 가중치 변화량
	
   int HstudyPattern[inputNodeCnt] = {1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0}; // HstudyPattern 학습 패턴
   int Hpoint[outputNodeCnt] = { 0,0,0,0,0,0,0,1,0,0 }; // HstudyPattern 교사 신호
   double HHidToOut[hiddenNodeCnt], // HstudyPattern 은닉층 -> 출력층 출력 값
      Hresult[outputNodeCnt], // HstudyPattern 교사 신호 결과
      HoutputDelta[outputNodeCnt], // HstudyPattern 출력층 오차 계산
      HhiddenDelta[hiddenNodeCnt], // HstudyPattern 은닉층 오차 계산
      HHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // HstudyPattern 은닉층 -> 출력층 가중치
      HInToHidWeight[hiddenNodeCnt][inputNodeCnt], // HstudyPattern 입력층 -> 은닉층 가중치
      HHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // HstudyPattern 가중치 변화량
      HInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // HstudyPattern 가중치 변화량
	
   int IstudyPattern[inputNodeCnt] = {0,1,1,1,0,1,0,0,0,0,1,0,1,1,0,1,0,0,1,0,0,1,1,1,0}; // IstudyPattern 학습 패턴
   int Ipoint[outputNodeCnt] = { 0,0,0,0,0,0,0,0,1,0 }; // IstudyPattern 교사 신호
   double IHidToOut[hiddenNodeCnt], // IstudyPattern 은닉층 -> 출력층 출력 값
      Iresult[outputNodeCnt], // IstudyPattern 교사 신호 결과
      IoutputDelta[outputNodeCnt], // IstudyPattern 출력층 오차 계산
      IhiddenDelta[hiddenNodeCnt], // IstudyPattern 은닉층 오차 계산
      IHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // IstudyPattern 은닉층 -> 출력층 가중치
      IInToHidWeight[hiddenNodeCnt][inputNodeCnt], // IstudyPattern 입력층 -> 은닉층 가중치
      IHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // IstudyPattern 가중치 변화량
      IInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // IstudyPattern 가중치 변화량
	
   int JstudyPattern[inputNodeCnt] = {1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0}; // JstudyPattern 학습 패턴
   int Jpoint[outputNodeCnt] = { 0,0,0,0,0,0,0,0,0,1 }; // JstudyPattern 교사 신호
   double JHidToOut[hiddenNodeCnt], // JstudyPattern 은닉층 -> 출력층 출력 값
      Jresult[outputNodeCnt], // JstudyPattern 교사 신호 결과
      JoutputDelta[outputNodeCnt], // JstudyPattern 출력층 오차 계산
      JhiddenDelta[hiddenNodeCnt], // JstudyPattern 은닉층 오차 계산
      JHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // JstudyPattern 은닉층 -> 출력층 가중치
      JInToHidWeight[hiddenNodeCnt][inputNodeCnt], // JstudyPattern 입력층 -> 은닉층 가중치
      JHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // JstudyPattern 가중치 변화량
      JInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // JstudyPattern 가중치 변화량

   //가중치 초기화
   double AoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // AstudyPattern 은닉층 -> 출력층 현재 가중치
	  AoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // AstudyPattern 입력층 -> 은닉층 현재 가중치
	  BoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // BstudyPattern 은닉층 -> 출력층 현재 가중치
	  BoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // BstudyPattern 입력층 -> 은닉층 현재 가중치
	  CoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // CstudyPattern 은닉층 -> 출력층 현재 가중치
	  CoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // CstudyPattern 입력층 -> 은닉층 현재 가중치
	  DoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // DstudyPattern 은닉층 -> 출력층 현재 가중치
	  DoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // DstudyPattern 입력층 -> 은닉층 현재 가중치
	  EoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // EstudyPattern 은닉층 -> 출력층 현재 가중치
	  EoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // EstudyPattern 입력층 -> 은닉층 현재 가중치
	  ForiginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // FstudyPattern 은닉층 -> 출력층 현재 가중치
	  ForiginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // FstudyPattern 입력층 -> 은닉층 현재 가중치
	  GoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // GstudyPattern 은닉층 -> 출력층 현재 가중치
	  GoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // GstudyPattern 입력층 -> 은닉층 현재 가중치
	  HoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // HstudyPattern 은닉층 -> 출력층 현재 가중치
	  HoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // HstudyPattern 입력층 -> 은닉층 현재 가중치
	  IoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // IstudyPattern 은닉층 -> 출력층 현재 가중치
	  IoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // IstudyPattern 입력층 -> 은닉층 현재 가중치
	  JoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // JstudyPattern 은닉층 -> 출력층 현재 가중치
	  JoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt]; // JstudyPattern 입력층 -> 은닉층 현재 가중치

   for (int i = 0; i < outputNodeCnt; i++) {
      for (int j = 0; j < hiddenNodeCnt; j++) {
         AoriginHidToOutWeight[i][j] = weight;
         BoriginHidToOutWeight[i][j] = weight;
         CoriginHidToOutWeight[i][j] = weight;
         DoriginHidToOutWeight[i][j] = weight;
		 EoriginHidToOutWeight[i][j] = weight;
		 ForiginHidToOutWeight[i][j] = weight;
		 GoriginHidToOutWeight[i][j] = weight;
		 HoriginHidToOutWeight[i][j] = weight;
		 IoriginHidToOutWeight[i][j] = weight;
		 JoriginHidToOutWeight[i][j] = weight;
      }
   }

   for (int i = 0; i < hiddenNodeCnt; i++) {
      for (int j = 0; j < inputNodeCnt; j++) {
         AoriginInToHidWeight[i][j] = weight;
         BoriginInToHidWeight[i][j] = weight;
         CoriginInToHidWeight[i][j] = weight;
		 DoriginInToHidWeight[i][j] = weight;
		 EoriginInToHidWeight[i][j] = weight;
		 ForiginInToHidWeight[i][j] = weight;
		 GoriginInToHidWeight[i][j] = weight;
		 HoriginInToHidWeight[i][j] = weight;
		 IoriginInToHidWeight[i][j] = weight;
		 JoriginInToHidWeight[i][j] = weight;
      }
   }

   // studyPattern 학습 시작
   while (true) {
   start:
      epoch++; // 학습 싸이클 횟수 증가

	  // AstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = AstudyPattern[j] * AoriginInToHidWeight[i][j];
            sum += tmp;
         }
         AHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = AHidToOut[j] * AoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Aresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         AoutputDelta[i] = Aresult[i] * (1 - Aresult[i])*(Apoint[i] - Aresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = AoutputDelta[j] * AoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         AhiddenDelta[i] = AHidToOut[i] * (1 - AHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            AHidToOutWeight[i][j] = AoriginHidToOutWeight[i][j] + (eta * AoutputDelta[i] * AhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            AInToHidWeight[i][j] = AoriginInToHidWeight[i][j] + (eta * AhiddenDelta[i] * AstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            AHidToOutCompare[i][j] = AoriginHidToOutWeight[i][j] - AHidToOutWeight[i][j];
            AoriginHidToOutWeight[i][j] = AHidToOutWeight[i][j];

            AInToHidCompare[i][j] = AoriginInToHidWeight[i][j] - AInToHidWeight[i][j];
            AoriginInToHidWeight[i][j] = AInToHidWeight[i][j];
         }
      }

	  // BstudyPattern 학습 시작

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = BstudyPattern[j] * BoriginInToHidWeight[i][j];
            sum += tmp;
         }
         BHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = BHidToOut[j] * BoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Bresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         BoutputDelta[i] = Bresult[i] * (1 - Bresult[i])*(Bpoint[i] - Bresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = BoutputDelta[j] * BoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         BhiddenDelta[i] = BHidToOut[i] * (1 - BHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            BHidToOutWeight[i][j] = BoriginHidToOutWeight[i][j] + (eta * BoutputDelta[i] * BhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            BInToHidWeight[i][j] = BoriginInToHidWeight[i][j] + (eta * BhiddenDelta[i] * BstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            BHidToOutCompare[i][j] = BoriginHidToOutWeight[i][j] - BHidToOutWeight[i][j];
            BoriginHidToOutWeight[i][j] = BHidToOutWeight[i][j];

            BInToHidCompare[i][j] = BoriginInToHidWeight[i][j] - BInToHidWeight[i][j];
            BoriginInToHidWeight[i][j] = BInToHidWeight[i][j];
         }
      }

      // CstudyPattern 학습 시작

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = CstudyPattern[j] * CoriginInToHidWeight[i][j];
            sum += tmp;
         }
         CHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = CHidToOut[j] * CoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Cresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         CoutputDelta[i] = Cresult[i] * (1 - Cresult[i])*(Cpoint[i] - Cresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = CoutputDelta[j] * CoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         ChiddenDelta[i] = CHidToOut[i] * (1 - CHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            CHidToOutWeight[i][j] = CoriginHidToOutWeight[i][j] + (eta * CoutputDelta[i] * ChiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            CInToHidWeight[i][j] = CoriginInToHidWeight[i][j] + (eta * ChiddenDelta[i] * CstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            CHidToOutCompare[i][j] = CoriginHidToOutWeight[i][j] - CHidToOutWeight[i][j];
            CoriginHidToOutWeight[i][j] = CHidToOutWeight[i][j];

            CInToHidCompare[i][j] = CoriginInToHidWeight[i][j] - CInToHidWeight[i][j];
            CoriginInToHidWeight[i][j] = CInToHidWeight[i][j];
         }
      }
	   
	  // DstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = DstudyPattern[j] * DoriginInToHidWeight[i][j];
            sum += tmp;
         }
         DHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = DHidToOut[j] * DoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Dresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         DoutputDelta[i] = Dresult[i] * (1 - Dresult[i])*(Dpoint[i] - Dresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = DoutputDelta[j] * DoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         DhiddenDelta[i] = DHidToOut[i] * (1 - DHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            DHidToOutWeight[i][j] = DoriginHidToOutWeight[i][j] + (eta * DoutputDelta[i] * DhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            DInToHidWeight[i][j] = DoriginInToHidWeight[i][j] + (eta * DhiddenDelta[i] * DstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            DHidToOutCompare[i][j] = DoriginHidToOutWeight[i][j] - DHidToOutWeight[i][j];
            DoriginHidToOutWeight[i][j] = DHidToOutWeight[i][j];

            DInToHidCompare[i][j] = DoriginInToHidWeight[i][j] - DInToHidWeight[i][j];
            DoriginInToHidWeight[i][j] = DInToHidWeight[i][j];
         }
      }
	   
	  // EstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = EstudyPattern[j] * EoriginInToHidWeight[i][j];
            sum += tmp;
         }
         EHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = EHidToOut[j] * EoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Eresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         EoutputDelta[i] = Eresult[i] * (1 - Eresult[i])*(Epoint[i] - Eresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = EoutputDelta[j] * EoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         EhiddenDelta[i] = EHidToOut[i] * (1 - EHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            EHidToOutWeight[i][j] = EoriginHidToOutWeight[i][j] + (eta * EoutputDelta[i] * EhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            EInToHidWeight[i][j] = EoriginInToHidWeight[i][j] + (eta * EhiddenDelta[i] * EstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            EHidToOutCompare[i][j] = EoriginHidToOutWeight[i][j] - EHidToOutWeight[i][j];
            EoriginHidToOutWeight[i][j] = EHidToOutWeight[i][j];

            EInToHidCompare[i][j] = EoriginInToHidWeight[i][j] - EInToHidWeight[i][j];
            EoriginInToHidWeight[i][j] = EInToHidWeight[i][j];
         }
      }
	   
	  // FstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = FstudyPattern[j] * ForiginInToHidWeight[i][j];
            sum += tmp;
         }
         FHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = FHidToOut[j] * ForiginHidToOutWeight[i][j];
            sum += tmp;
         }
         Fresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         FoutputDelta[i] = Fresult[i] * (1 - Fresult[i])*(Fpoint[i] - Fresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = FoutputDelta[j] * ForiginHidToOutWeight[j][i];
            sum += tmp;
         }
         FhiddenDelta[i] = FHidToOut[i] * (1 - FHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            FHidToOutWeight[i][j] = ForiginHidToOutWeight[i][j] + (eta * FoutputDelta[i] * FhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            FInToHidWeight[i][j] = ForiginInToHidWeight[i][j] + (eta * FhiddenDelta[i] * FstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            FHidToOutCompare[i][j] = ForiginHidToOutWeight[i][j] - FHidToOutWeight[i][j];
            ForiginHidToOutWeight[i][j] = FHidToOutWeight[i][j];

            FInToHidCompare[i][j] = ForiginInToHidWeight[i][j] - FInToHidWeight[i][j];
            ForiginInToHidWeight[i][j] = FInToHidWeight[i][j];
         }
      }
	   
	  // GstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = GstudyPattern[j] * GoriginInToHidWeight[i][j];
            sum += tmp;
         }
         GHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = GHidToOut[j] * GoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Gresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         GoutputDelta[i] = Gresult[i] * (1 - Gresult[i])*(Gpoint[i] - Gresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = GoutputDelta[j] * GoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         GhiddenDelta[i] = GHidToOut[i] * (1 - GHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            GHidToOutWeight[i][j] = GoriginHidToOutWeight[i][j] + (eta * GoutputDelta[i] * GhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            GInToHidWeight[i][j] = GoriginInToHidWeight[i][j] + (eta * GhiddenDelta[i] * GstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            GHidToOutCompare[i][j] = GoriginHidToOutWeight[i][j] - GHidToOutWeight[i][j];
            GoriginHidToOutWeight[i][j] = GHidToOutWeight[i][j];

            GInToHidCompare[i][j] = GoriginInToHidWeight[i][j] - GInToHidWeight[i][j];
            GoriginInToHidWeight[i][j] = GInToHidWeight[i][j];
         }
      }
	   
	  // HstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = HstudyPattern[j] * HoriginInToHidWeight[i][j];
            sum += tmp;
         }
         HHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = HHidToOut[j] * HoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Hresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         HoutputDelta[i] = Hresult[i] * (1 - Hresult[i])*(Hpoint[i] - Hresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = HoutputDelta[j] * HoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         HhiddenDelta[i] = HHidToOut[i] * (1 - HHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            HHidToOutWeight[i][j] = HoriginHidToOutWeight[i][j] + (eta * HoutputDelta[i] * HhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            HInToHidWeight[i][j] = HoriginInToHidWeight[i][j] + (eta * HhiddenDelta[i] * HstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            HHidToOutCompare[i][j] = HoriginHidToOutWeight[i][j] - HHidToOutWeight[i][j];
            HoriginHidToOutWeight[i][j] = HHidToOutWeight[i][j];

            HInToHidCompare[i][j] = HoriginInToHidWeight[i][j] - HInToHidWeight[i][j];
            HoriginInToHidWeight[i][j] = HInToHidWeight[i][j];
         }
      }
	   
	  // IstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = IstudyPattern[j] * IoriginInToHidWeight[i][j];
            sum += tmp;
         }
         IHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = IHidToOut[j] * IoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Iresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         IoutputDelta[i] = Iresult[i] * (1 - Iresult[i])*(Ipoint[i] - Iresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = IoutputDelta[j] * IoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         IhiddenDelta[i] = IHidToOut[i] * (1 - IHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            IHidToOutWeight[i][j] = IoriginHidToOutWeight[i][j] + (eta * IoutputDelta[i] * IhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            IInToHidWeight[i][j] = IoriginInToHidWeight[i][j] + (eta * IhiddenDelta[i] * IstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            IHidToOutCompare[i][j] = IoriginHidToOutWeight[i][j] - IHidToOutWeight[i][j];
            IoriginHidToOutWeight[i][j] = IHidToOutWeight[i][j];

            IInToHidCompare[i][j] = IoriginInToHidWeight[i][j] - IInToHidWeight[i][j];
            IoriginInToHidWeight[i][j] = IInToHidWeight[i][j];
         }
      }
	   
	  // JstudyPattern 학습

      // 입력층 -> 은닉층의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = JstudyPattern[j] * JoriginInToHidWeight[i][j];
            sum += tmp;
         }
         JHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉층 -> 출력층의 출력값
      for (int i = 0; i < outputNodeCnt; i++) {
         sum = 0;
         tmp = 0;
         for (int j = 0; j < hiddenNodeCnt; j++) {
            tmp = JHidToOut[j] * JoriginHidToOutWeight[i][j];
            sum += tmp;
         }
         Jresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 출력층 오차계산(델타)
      for (int i = 0; i < outputNodeCnt; i++) {
         JoutputDelta[i] = Jresult[i] * (1 - Jresult[i])*(Jpoint[i] - Jresult[i]);
      }

      // 은닉층 오차계산(델타)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < outputNodeCnt; j++) {
            tmp = JoutputDelta[j] * JoriginHidToOutWeight[j][i];
            sum += tmp;
         }
         JhiddenDelta[i] = JHidToOut[i] * (1 - JHidToOut[i]) * sum;
      }

      // 가중치 수정(은닉층 -> 출력층)
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            JHidToOutWeight[i][j] = JoriginHidToOutWeight[i][j] + (eta * JoutputDelta[i] * JhiddenDelta[j]);
         }
      }

      // 가중치 수정(입력층 -> 은닉층)
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            JInToHidWeight[i][j] = JoriginInToHidWeight[i][j] + (eta * JhiddenDelta[i] * JstudyPattern[j]);
         }
      }

      // 가중치 변화량 저장
      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            JHidToOutCompare[i][j] = JoriginHidToOutWeight[i][j] - JHidToOutWeight[i][j];
            JoriginHidToOutWeight[i][j] = JHidToOutWeight[i][j];

            JInToHidCompare[i][j] = JoriginInToHidWeight[i][j] - JInToHidWeight[i][j];
            JoriginInToHidWeight[i][j] = JInToHidWeight[i][j];
         }
      }

      // 가중치 변화량 검사

      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            if (AHidToOutCompare[i][j] > 0.00001 || BHidToOutCompare[i][j] > 0.00001 || CHidToOutCompare[i][j] > 0.00001 || DHidToOutCompare[i][j] > 0.00001 || EHidToOutCompare[i][j] > 0.00001 || FHidToOutCompare[i][j] > 0.00001 || GHidToOutCompare[i][j] > 0.00001 || HHidToOutCompare[i][j] > 0.00001 || IHidToOutCompare[i][j] > 0.00001 || JHidToOutCompare[i][j] > 0.00001) {
               goto start;
            }
            else {
               goto end;
            }
         }
      }

   end:
      for (int i = 0; i < hiddenNodeCnt; i++) {
         for (int j = 0; j < inputNodeCnt; j++) {
            if (AInToHidCompare[i][j] > 0.00001 || BInToHidCompare[i][j] > 0.00001 || CInToHidCompare[i][j] > 0.00001 || DInToHidCompare[i][j] > 0.00001 || EInToHidCompare[i][j] > 0.00001 || FInToHidCompare[i][j] > 0.00001 || GInToHidCompare[i][j] > 0.00001 || HInToHidCompare[i][j] > 0.00001 || IInToHidCompare[i][j] > 0.00001 || JInToHidCompare[i][j] > 0.00001) {
               goto start;
            }
         }
      }
      break;
   }

   cout << "학습이 완료 되었습니다 / epoch : " << epoch << endl; // 싸이클 횟수 출력
   cout << "---------------------------------------------------------";
   cout << endl;

   // inputPattern 입력
   int inputPattern[inputNodeCnt] = {}; // InputPattern
   double inputPoint[outputNodeCnt]; // InputPattern 교사 신호
   double InputAHidToOut[hiddenNodeCnt], // InputPattern AstudyPattern에 대한 은닉층 -> 출력층 값
	  InputAresult[outputNodeCnt], // InputPattern AstudyPattern에 대한 결과
	  InputBHidToOut[hiddenNodeCnt], // InputPattern BstudyPattern에 대한 은닉층 -> 출력층 값
	  InputBresult[outputNodeCnt], // InputPattern BstudyPattern에 대한 결과
	  InputCHidToOut[hiddenNodeCnt], // InputPattern CstudyPattern에 대한 은닉층 -> 출력층 값
	  InputCresult[outputNodeCnt], // InputPattern CstudyPattern에 대한 결과
	  InputDHidToOut[hiddenNodeCnt], // InputPattern DstudyPattern에 대한 은닉층 -> 출력층 값
	  InputDresult[outputNodeCnt], // InputPattern DstudyPattern에 대한 결과
	  InputEHidToOut[hiddenNodeCnt], // InputPattern EstudyPattern에 대한 은닉층 -> 출력층 값
	  InputEresult[outputNodeCnt], // InputPattern EstudyPattern에 대한 결과
	  InputFHidToOut[hiddenNodeCnt], // InputPattern FstudyPattern에 대한 은닉층 -> 출력층 값
	  InputFresult[outputNodeCnt], // InputPattern FstudyPattern에 대한 결과
	  InputGHidToOut[hiddenNodeCnt], // InputPattern GstudyPattern에 대한 은닉층 -> 출력층 값
	  InputGresult[outputNodeCnt], // InputPattern GstudyPattern에 대한 결과
	  InputHHidToOut[hiddenNodeCnt], // InputPattern HstudyPattern에 대한 은닉층 -> 출력층 값
	  InputHresult[outputNodeCnt], // InputPattern HstudyPattern에 대한 결과
	  InputIHidToOut[hiddenNodeCnt], // InputPattern IstudyPattern에 대한 은닉층 -> 출력층 값
	  InputIresult[outputNodeCnt], // InputPattern IstudyPattern에 대한 결과
	  InputJHidToOut[hiddenNodeCnt], // InputPattern JstudyPattern에 대한 은닉층 -> 출력층 값
	  InputJresult[outputNodeCnt]; // InputPattern JstudyPattern에 대한 결과

   cout << "패턴 입력을 입력하세요 유효 : 1, 빈칸 : 0" << endl;
   for (int i = 0; i < inputNodeCnt; i++) {
      cin >> inputPattern[i];
   }

   // inputPattern 확인
   cout << endl;
   cout << "---------------------------------------------------------" << endl;
   cout << "입력 패턴" << endl;
   for (int i = 0; i < inputNodeCnt; i++) {
      if (inputPattern[i] == 1) {
         cout << "▨ ";
      }
      else {
         cout << "□ ";
      }
      if (i % 5 == 4) {
         cout << endl;
      }
   }
   cout << endl;

   // 결과 계산
	
   // InputPattern 은닉층 AstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * AInToHidWeight[i][j];
         sum += tmp;
      }
      InputAHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 AstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputAHidToOut[j] * AHidToOutWeight[i][j];
         sum += tmp;
      }
      InputAresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 은닉층 BstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * BInToHidWeight[i][j];
         sum += tmp;
      }
      InputBHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 BstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputBHidToOut[j] * BHidToOutWeight[i][j];
         sum += tmp;
      }
      InputBresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 은닉층 CstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * CInToHidWeight[i][j];
         sum += tmp;
      }
      InputCHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 CstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputCHidToOut[j] * CHidToOutWeight[i][j];
         sum += tmp;
      }
      InputCresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 DstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * DInToHidWeight[i][j];
         sum += tmp;
      }
      InputDHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 DstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputDHidToOut[j] * DHidToOutWeight[i][j];
         sum += tmp;
      }
      InputDresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 EstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * EInToHidWeight[i][j];
         sum += tmp;
      }
      InputEHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 EstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputEHidToOut[j] * EHidToOutWeight[i][j];
         sum += tmp;
      }
      InputEresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 FstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * FInToHidWeight[i][j];
         sum += tmp;
      }
      InputFHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 FstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputFHidToOut[j] * FHidToOutWeight[i][j];
         sum += tmp;
      }
      InputFresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 GstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * GInToHidWeight[i][j];
         sum += tmp;
      }
      InputGHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 GstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputGHidToOut[j] * GHidToOutWeight[i][j];
         sum += tmp;
      }
      InputGresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 HstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * HInToHidWeight[i][j];
         sum += tmp;
      }
      InputHHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 HstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputHHidToOut[j] * HHidToOutWeight[i][j];
         sum += tmp;
      }
      InputHresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 IstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * IInToHidWeight[i][j];
         sum += tmp;
      }
      InputIHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 IstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputIHidToOut[j] * IHidToOutWeight[i][j];
         sum += tmp;
      }
      InputIresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }
	
   // InputPattern 은닉층 JstudyPattern 출력 값 계산
   for (int i = 0; i < hiddenNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < inputNodeCnt; j++) {
         tmp = inputPattern[j] * JInToHidWeight[i][j];
         sum += tmp;
      }
      InputIHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // InputPattern 출력층 JstudyPattern 출력 값 계산
   for (int i = 0; i < outputNodeCnt; i++) {
      sum = 0;
      for (int j = 0; j < hiddenNodeCnt; j++) {
         tmp = InputIHidToOut[j] * JHidToOutWeight[i][j];
         sum += tmp;
      }
      InputJresult[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
   }

   // point(교사 신호) 값과 가장 가까운 값 찾기
   double InputPatternResult[outputNodeCnt];
   for (int i = 0; i < outputNodeCnt; i++) {
      InputPatternResult[i] = InputAresult[i] + InputBresult[i] + InputCresult[i] + InputDresult[i] + InputEresult[i] + InputFresult[i] + InputGresult[i] + InputHresult[i] + InputIresult[i] + InputJresult[i];
      InputPatternResult[i] = fabs(InputPatternResult[i]); // 절댓값
   }

   double temp = 0;
   for (int i = 0; i < outputNodeCnt; i++) {
      if (temp < InputPatternResult[i]) {
         temp = InputPatternResult[i];
      }
   }
   for (int i = 0; i < outputNodeCnt; i++) {
      inputPoint[i] = InputPatternResult[i] / temp;
   }

   // 최종 결과 계산
   if (inputPoint[0] == 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // AstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = AstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] == 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // BstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = BstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] == 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // CstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = CstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] == 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // DstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = DstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] == 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // EstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = EstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] == 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // FstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = FstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] == 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // GstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = GstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] == 1 && inputPoint[8] != 1 && inputPoint[9] != 1) { // GstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = HstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] == 1 && inputPoint[9] != 1) { // IstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = IstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] != 1 && inputPoint[3] != 1 && inputPoint[4] != 1 && inputPoint[5] != 1 && inputPoint[6] != 1 && inputPoint[7] != 1 && inputPoint[8] != 1 && inputPoint[9] == 1) { // JstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = JstudyPattern[i];
      }
   }
	
	for(int i=0; i<outputNodeCnt; i++) {
		cout << inputPoint[i] << " ";
	}

   // 결과 패턴 출력
   cout << endl;
   cout << "결과 패턴" << endl;
   for (int i = 0; i < inputNodeCnt; i++) {
      if (inputPattern[i] == 1) {
         cout << "▨ ";
      }
      else {
         cout << "□ ";
      }
      if (i % 5 == 4) {
         cout << endl;
      }
   }
   cout << endl;

   return 0;
}

#include <iostream>
#include <math.h>

using namespace std;

int outputNodeCnt = 3; // 출력층 노트 갯수
int hiddenNodeCnt = 5; // 은닉층 노드 갯수
int inputNodeCnt = 25; // 입력층 노드 갯수

double weight = 0.7; // 가중치
double eta = 0.8; // eta 값
double offset = 0.5; // offset 값
int epoch = 0; // epoch 학습 모델 가중치 수정 싸이클 횟수 계산
double tmp, sum;

int main() {
   int AstudyPattern[inputNodeCnt] = {1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1}; // AstudyPattern 학습 패턴
   int Apoint[outputNodeCnt] = { 1,0,0 }; // AstudyPattern 교사 신호
   double AHidToOut[hiddenNodeCnt], // AstudyPattern 은닉층 -> 출력층 출력 값
      Aresult[outputNodeCnt], // AstudyPattern 교사 신호 결과
      AoutputDelta[outputNodeCnt], // AstudyPattern 출력층 오차 계산
      AhiddenDelta[hiddenNodeCnt], // AstudyPattern 은닉층 오차 계산
      AHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // AstudyPattern 은닉층 -> 출력층 가중치
      AInToHidWeight[hiddenNodeCnt][inputNodeCnt], // AstudyPattern 입력층 -> 은닉층 가중치
      AHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // AstudyPattern 가중치 변화량
      AInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // AstudyPattern 가중치 변화량


   int BstudyPattern[inputNodeCnt] = {1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1}; // BstudyPattern 학습 패턴
   int Bpoint[outputNodeCnt] = { 0,1,0 }; // BstudyPattern 교사 신호
   double BHidToOut[hiddenNodeCnt], // BstudyPattern 은닉층 -> 출력층 출력 값
      Bresult[outputNodeCnt], // BstudyPattern 교사 신호 결과
      BoutputDelta[outputNodeCnt], // BstudyPattern 출력층 오차 계산
      BhiddenDelta[hiddenNodeCnt], // BstudyPattern 은닉층 오차 계산
      BHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // BstudyPattern 은닉층 -> 출력층 가중치
      BInToHidWeight[hiddenNodeCnt][inputNodeCnt], // BstudyPattern 입력층 -> 은닉층 가중치
      BHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // BstudyPattern 가중치 변화량
      BInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // BstudyPattern 가중치 변화량


   int CstudyPattern[inputNodeCnt] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1}; // CstudyPattern 학습 패턴
   int Cpoint[outputNodeCnt] = { 0,0,1 }; // CstudyPattern 교사 신호
   double CHidToOut[hiddenNodeCnt], // CstudyPattern 은닉층 -> 출력층 출력 값
      Cresult[outputNodeCnt], // CstudyPattern 교사 신호 결과
      CoutputDelta[outputNodeCnt], // CstudyPattern 출력층 오차 계산
      ChiddenDelta[hiddenNodeCnt], // CstudyPattern 은닉층 오차 계산
      CHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // CstudyPattern 은닉층 -> 출력층 가중치
      CInToHidWeight[hiddenNodeCnt][inputNodeCnt], // CstudyPattern 입력층 -> 은닉층 가중치
      CHidToOutCompare[outputNodeCnt][hiddenNodeCnt], // CstudyPattern 가중치 변화량
      CInToHidCompare[hiddenNodeCnt][inputNodeCnt]; // CstudyPattern 가중치 변화량


   //가중치 초기화
   double AoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // AstudyPattern 은닉층 -> 출력층 현재 가중치
	  AoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // AstudyPattern 입력층 -> 은닉층 현재 가중치
	  BoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // BstudyPattern 은닉층 -> 출력층 현재 가중치
	  BoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt], // BstudyPattern 입력층 -> 은닉층 현재 가중치
	  CoriginHidToOutWeight[outputNodeCnt][hiddenNodeCnt], // CstudyPattern 은닉층 -> 출력층 현재 가중치
	  CoriginInToHidWeight[hiddenNodeCnt][inputNodeCnt]; // CstudyPattern 입력층 -> 은닉층 현재 가중치

   for (int i = 0; i < outputNodeCnt; i++) {
      for (int j = 0; j < hiddenNodeCnt; j++) {
         AoriginHidToOutWeight[i][j] = weight;
         BoriginHidToOutWeight[i][j] = weight;
         CoriginHidToOutWeight[i][j] = weight;
      }
   }

   for (int i = 0; i < hiddenNodeCnt; i++) {
      for (int j = 0; j < inputNodeCnt; j++) {
         AoriginInToHidWeight[i][j] = weight;
         BoriginInToHidWeight[i][j] = weight;
         CoriginInToHidWeight[i][j] = weight;
      }
   }

   // studyPattern 학습 시작
   while (true) {
   start:
      epoch++; // 학습 싸이클 횟수 증가

	  // AstudyPattern 학습

      // 입력층 -> 은닉충의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = AstudyPattern[j] * AoriginInToHidWeight[i][j];
            sum += tmp;
         }
         AHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉충 -> 출력층의 출력값
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

      // 은닉충 오차계산(델타)
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

      // 입력층 -> 은닉충의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = BstudyPattern[j] * BoriginInToHidWeight[i][j];
            sum += tmp;
         }
         BHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉충 -> 출력층의 출력값
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

      // 은닉충 오차계산(델타)
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

      // 입력층 -> 은닉충의 출력 값
      for (int i = 0; i < hiddenNodeCnt; i++) {
         sum = 0;
         for (int j = 0; j < inputNodeCnt; j++) {
            tmp = CstudyPattern[j] * CoriginInToHidWeight[i][j];
            sum += tmp;
         }
         CHidToOut[i] = (pow(eta, (sum - offset)) / (pow(eta, (sum - offset)) + 1));
      }

      // 은닉충 -> 출력층의 출력값
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

      // 은닉충 오차계산(델타)
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

      // 가중치 변화량 검사

      for (int i = 0; i < outputNodeCnt; i++) {
         for (int j = 0; j < hiddenNodeCnt; j++) {
            if (AHidToOutCompare[i][j] > 0.0001 || BHidToOutCompare[i][j] > 0.0001 || CHidToOutCompare[i][j] > 0.0001) {
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
            if (AInToHidCompare[i][j] > 0.0001 || BInToHidCompare[i][j] > 0.0001 || CInToHidCompare[i][j] > 0.0001) {
               goto start;
            }
         }
      }
      break;
   }

   cout << "학습이 완료 되었습니다 / 싸이클 횟수 : " << epoch << endl; // 싸이클 횟수 출력
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
	  InputCresult[outputNodeCnt]; // InputPattern CstudyPattern에 대한 결과

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
      if (i % hiddenNodeCnt == 4) {
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

   // point(교사 신호) 값과 가장 가까운 값 찾기
   double InputPatternResult[outputNodeCnt];
   for (int i = 0; i < 3; i++) {
      InputPatternResult[i] = InputAresult[i] + InputBresult[i] + InputCresult[i];
      InputPatternResult[i] = fabs(InputPatternResult[i]); // 절댓값
   }

   double temp = 0;
   for (int i = 0; i < 3; i++) {
      if (temp < InputPatternResult[i]) {
         temp = InputPatternResult[i];
      }
   }
   for (int i = 0; i < 3; i++) {
      inputPoint[i] = InputPatternResult[i] / temp;
   }

   // 최종 결과 계산
   if (inputPoint[0] == 1 && inputPoint[1] != 1 && inputPoint[2] != 1) { // AstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = AstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] == 1 && inputPoint[2] != 1) { // BstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = BstudyPattern[i];
      }
   }
   else if (inputPoint[0] != 1 && inputPoint[1] != 1 && inputPoint[2] == 1) { // CstudyPattern과 비교
      for (int i = 0; i < inputNodeCnt; i++) {
         inputPattern[i] = CstudyPattern[i];
      }
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
      if (i % hiddenNodeCnt == 4) {
         cout << endl;
      }
   }
   cout << endl;

   return 0;
}

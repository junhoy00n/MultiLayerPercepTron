package deeplearning;

import java.util.Scanner;

public class MultiLayerPercepTron_v2 {

	static int studyPatternCnt; // 학습한 패턴의 갯수
	static int outputNodeCnt; // 출력층 노드의 갯수
	static int hiddenNodeCnt = 24; // 은닉층 노드의 갯수
	static int inputNodeCnt; // 입력층 노드의 갯수
	static int epoch = 0; // epoch 초기 값
	
	static double offset = 0.8; // 임계값 설정
	static double eta = 0.5; // eta 값 설정
	static double CompareWeight = 0.001; // 가중치 변화량 오차 범위 지정
	
	// sigmoid 함수 구현
	public static double sigmoid(double x) {
		double result = 1 / (1 + Math.exp(-x));
		if(result > offset) { // sigmoid함수 실행 시 임계값(offset)을 넘어가면 1으로 설정
			result = 1;
		}
		
		return result;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		// 학습한 패턴에 대한 정보
		System.out.print("학습할 패턴의 갯수를 입력하세요 : ");
		studyPatternCnt = sc.nextInt(); // 학습패턴의 갯수 입력
		System.out.print("입력층 노드의 갯수를 입력하세요 : ");
		inputNodeCnt = sc.nextInt(); // 입력층 노드의 갯수 입력
		System.out.println("------------------------------------------------------------");
		System.out.println("학습 패턴을 입력하세요.   (유효 : 1 / 빈칸 : 0)");
		int[][] studyPattern = new int[studyPatternCnt][inputNodeCnt];
		for(int i=0; i<studyPatternCnt; i++) {
			for(int j=0; j<inputNodeCnt; j++) {
				studyPattern[i][j] = sc.nextInt(); // 학습 패턴 입력
			}
		}
		outputNodeCnt = studyPatternCnt;
		// 학습 패턴에 대한 교사신호
		int[][] point = new int[studyPatternCnt][outputNodeCnt];
		for(int i=0; i<studyPatternCnt; i++) {
			for(int j=0; j<outputNodeCnt; j++) {
				if(i == j) {
					point[i][j] = 1;
				}
				else {
					point[i][j] = 0;
				}
			}
		}
		
		double[] inTohidValue = new double[hiddenNodeCnt]; // 입력층 -> 은닉층 출력값 계산 배열
		double[] hidTooutValue = new double[outputNodeCnt]; // 은닉층 -> 출력층 출력값 계산 배열
		
		double[] outputDelta = new double[outputNodeCnt]; // 출력층 오차계산 배열
		double[] hiddenDelta = new double[hiddenNodeCnt]; // 은닉층 오차계산 배열
		
		double[][] CurrenthidTooutWeight = new double[hiddenNodeCnt][outputNodeCnt]; // 은닉층 -> 출력층 현재 가중치 배열
		for(int i=0; i<hiddenNodeCnt; i++) {
			for(int j=0; j<outputNodeCnt; j++) {
				CurrenthidTooutWeight[i][j] = ((Math.random() % 10) + 1) * 0.01; // 은닉층 -> 출력층 현재 가중치를 랜덤으로 지정
			}
		}
		double[][] UpdatehidTooutWeight = new double[hiddenNodeCnt][outputNodeCnt]; // 은닉층 -> 출력층 수정 가중치 배열
		double[][] ComparehidTooutWeight = new double[hiddenNodeCnt][outputNodeCnt]; // 은닉층 -> 출력층 가중치 변화량 배열
		double[][] CurrentinTohidWeight = new double[hiddenNodeCnt][inputNodeCnt]; // 입력층 -> 은닉층 현재 가중치 배열
		for(int i=0; i<hiddenNodeCnt; i++) {
			for(int j=0; j<inputNodeCnt; j++) {
				CurrentinTohidWeight[i][j] = ((Math.random() % 10) + 1) * 0.01; // 입력층 -> 은닉층 현재 가중치를 랜덤으로 지정
			}
		}
		double[][] UpdateinTohidWeight = new double[hiddenNodeCnt][inputNodeCnt]; // 입력층 -> 은닉층 수정 가중치 배열
		double[][] CompareinTohidWeight = new double[hiddenNodeCnt][inputNodeCnt]; // 입력층 -> 은닉층 가중치 변화량 배열
		
		// 학습 시작
		while(true) {
			double x;
			double temp;
			
			int checkSum = 0;
			
			for(int n=0; n<studyPatternCnt; n++) {
				
				// 입력층 -> 은닉층 출력값 계산
				for(int i=0; i<hiddenNodeCnt; i++) {
					x = 0;
					for(int j=0; j<inputNodeCnt; j++) {
						x += studyPattern[n][j] * CurrentinTohidWeight[i][j];
					}
					inTohidValue[i] = sigmoid(x);
				}
				
				// 은닉층 -> 출력층 출력값 계산
				for(int i=0; i<outputNodeCnt; i++) {
					x = 0;
					for(int j=0; j<hiddenNodeCnt; j++) {
						x += inTohidValue[j] * CurrenthidTooutWeight[j][i];
					}
					hidTooutValue[i] = sigmoid(x);
				}
				
				// 출력층 오차 계산
				for(int i=0; i<outputNodeCnt; i++) {
					outputDelta[i] = hidTooutValue[i] * (1 - hidTooutValue[i]) * (point[n][i] - hidTooutValue[i]);
				}
				
				// 은닉층 오차 계산
				for(int i=0; i<hiddenNodeCnt; i++) {
					temp = 0;
					for(int j=0; j<outputNodeCnt; j++) {
						temp += outputDelta[j] * CurrenthidTooutWeight[i][j];
					}
					hiddenDelta[i] = inTohidValue[i] * (1 - inTohidValue[i]) * temp;
				}
				
				checkSum = 0;
				// 가중치 수정 (은닉층 -> 출력층)
				for(int i=0; i<hiddenNodeCnt; i++) {
					for(int j=0; j<outputNodeCnt; j++) {
						UpdatehidTooutWeight[i][j] = CurrenthidTooutWeight[i][j] + eta * outputDelta[j] * inTohidValue[i];
						ComparehidTooutWeight[i][j] = Math.abs(UpdatehidTooutWeight[i][j] - CurrenthidTooutWeight[i][j]);
						CurrenthidTooutWeight[i][j] = UpdatehidTooutWeight[i][j];
						
						if(ComparehidTooutWeight[i][j] < CompareWeight) { // 은닉층 -> 출력층의 가중치가 모두 오차범위(CompareSize) 안에 들어오는지 확인
							checkSum++;
						}
					}
				}
				
				// 가중치 수정 (입력층 -> 은닉층)
				for(int i=0; i<hiddenNodeCnt; i++) {
					for(int j=0; j<inputNodeCnt; j++) {
						UpdateinTohidWeight[i][j] = CurrentinTohidWeight[i][j] + eta * hiddenDelta[i] * studyPattern[n][j];
						CompareinTohidWeight[i][j] = Math.abs(UpdateinTohidWeight[i][j] - CurrentinTohidWeight[i][j]);
						CurrentinTohidWeight[i][j] = UpdateinTohidWeight[i][j];
						
						if(CompareinTohidWeight[i][j] < CompareWeight) { // 입력층 -> 은닉층의 가중치가 모두 오차범위(CompareSize) 안에 들어오는지 확인
							checkSum++;
						}
					}
				}
				
				// 노드간의 연결 선의 수는 은닉층 노드의 수 * (입력층 노드의 수 + 출력층 노드의 수)이기 때문에 모든 가중치가 오차범위(CompareSize) 안에 들어오면 학습 종료
				if(checkSum == hiddenNodeCnt * (inputNodeCnt + outputNodeCnt)) {
					break;
				}
				
				epoch++; // 학습패턴을 전방향 학습과정에서 역방향 학습과정까지 모두 완료
			}
			
			// 노드간의 연결 선의 수는 은닉층 노드의 수 * (입력층 노드의 수 + 출력층 노드의 수)이기 때문에 모든 가중치가 오차범위(CompareSize) 안에 들어오면 학습 종료
			if(checkSum == hiddenNodeCnt * (inputNodeCnt + outputNodeCnt)) {
				break;
			}
		}
		System.out.println("--------------------------------------------------");
		System.out.println("학습이 완료 되었습니다 / epoch : " + epoch); // 학습이 완료되었음을 알리고 epoch를 몇번 돌았는지 알림
		System.out.println("--------------------------------------------------");
		
		// 학습한 패턴에 대한 테스트 진행 여부 확인
		while(true) {
			System.out.println("테스트를 진행하시겠습니까?   (진행 : 1 / 종료 : 0)");
			int progressStatus = sc.nextInt();
			if(progressStatus == 1) { // 학습한 패턴에 대한 테스트를 계속 진행
				System.out.println();
				System.out.println("테스트 패턴을 입력하세요.   (유효 : 1 / 빈칸 : 0)");
				
				// 노이즈 패턴 입력
				int[] inputPattern = new int[inputNodeCnt];
				for(int i=0; i<inputNodeCnt; i++) {
					inputPattern[i] = sc.nextInt();
				}
				
				// 1과 0으로 받은 노이즈 패턴을 픽셀로 변환
				System.out.println("--------------------------------------------------");
				System.out.println("입력 패턴 : ");
				for(int i=0; i<inputNodeCnt; i++) {
					if(inputPattern[i] == 1) {
						System.out.print("▨ ");
					}
					else if(inputPattern[i] != 1) {
						System.out.print("□ ");
					}
					if(i % (studyPatternCnt / 2) == (studyPatternCnt / 2) - 1) {
						System.out.println(); // 1차원 배열을 2차원 배열로 변환하기 위한 줄바꿈 시행
					}
				}
				
				// inputPattern에 대한 입력층 -> 은닉층 출력값 계산
				double x;
				for(int i=0; i<hiddenNodeCnt; i++) {
					x = 0;
					for(int j=0; j<inputNodeCnt; j++) {
						x += inputPattern[j] * UpdateinTohidWeight[i][j];
					}
					inTohidValue[i] = sigmoid(x);
				}
				
				// inputPattern에 대한 은닉층 -> 출력층 출력값 계산
				for(int i=0; i<outputNodeCnt; i++) {
					x = 0;
					for(int j=0; j<hiddenNodeCnt; j++) {
						x += inTohidValue[j] * UpdatehidTooutWeight[j][i];
					}
					hidTooutValue[i] = sigmoid(x);
				}
				
				// inputPattern에 대한 출력값을 학습한 패턴의 교사신호와 비교하기 위한 최종 계산
				double max = 0;
				for(int i=0; i<outputNodeCnt; i++) {
					if(max < hidTooutValue[i]) {
						max = hidTooutValue[i];
					}
				}
				double[] inputPoint = new double[outputNodeCnt];
				for(int i=0; i<outputNodeCnt; i++) {
					inputPoint[i] = hidTooutValue[i] / max;
				}
				
				// inputPattern과 학습패턴을 비교하여 일치하는 교사신호에 대한 학습 패턴을 입력
				for(int n=0; n<studyPatternCnt; n++) {
					for(int i=0; i<inputNodeCnt; i++) {
						if(inputPoint[n] == 1) {
							inputPattern[i] = studyPattern[n][i];
						}
					}
				}
				
				System.out.println();
				System.out.println("결과 패턴 : "); // 결과 패턴 출력
				for(int i=0; i<inputNodeCnt; i++) {
					if(inputPattern[i] == 1) {
						System.out.print("▨ ");
					}
					else if(inputPattern[i] == 0) {
						System.out.print("□ ");
					}
					if(i % (studyPatternCnt / 2) == (studyPatternCnt / 2) - 1) {
						System.out.println(); // 1차원 배열을 2차원 배열로 변환하기 위한 줄바꿈 시행
					}
				}
				System.out.println("--------------------------------------------------");
			}
			
			else if(progressStatus == 0) { // 학습한 패턴에 대한 테스트 종료
				break;
			}
		}
	}
}

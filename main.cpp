// エンジンコード インクルード
#include <Novice.h>
#include <ImGuiManager.h>

// 自作コード インクルード
#include"./Code/hedaer/MathTool.h"
#include"./Code/hedaer/MatrixCamera.h"

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const float kWindowSizeX = 1280.0f;
const float kWindowSizeY = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(kWindowSizeX), int(kWindowSizeY));

	// ワールドの拡縮・回転・平行移動を設定
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	// カメラの拡縮・回転・平行移動を設定
	Vector3 cameraScale = { 1.0f,1.0f,1.0f };
	Vector3 cameraRotate = { 0.4f,0.3f,0.0f };
	Vector3 cameraPosition = { -3.0f,4.0f,-8.00f };

	// 行列カメラのクラスを宣言・初期化
	MatrixCamera* camera = new MatrixCamera({ kWindowSizeX,kWindowSizeY });
	camera->Initialize();

	// 表示用の変数
	//const int kRowHeight = 30;
	//const int kColumnWidth = 600;

	//
	// 課題用変数　ここから
	//

	// ベジエ曲線の制御点
	Vector3 controlPoints[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f}
	};

	// ベジエ曲線の制御点のスクリーン座標
	Vector3 screenControlPos[3] = {};

	// 色
	uint32_t color = 0xFFFFFFFF;

	//
	//　課題用変数　ここまで
	//


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2Int mousePos = { 0,0 };
	Vector2Int preMousePos = { 0,0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// マウスの入力を受け取る
		preMousePos = mousePos;
		Novice::GetMousePosition(&mousePos.x, &mousePos.y);

		///
		/// ↓更新処理ここから
		///

		// マウス右クリック+カーソル移動で回転
		if (Novice::IsPressMouse(1)) {

			if (0 < (preMousePos.x - mousePos.x)) {
				cameraRotate.y += 0.01f;
			}

			if (0 > (preMousePos.x - mousePos.x)) {
				cameraRotate.y -= 0.01f;
			}

			if (0 < (preMousePos.y - mousePos.y)) {
				cameraRotate.x += 0.01f;
			}

			if (0 > (preMousePos.y - mousePos.y)) {
				cameraRotate.x -= 0.01f;
			}

		}

		// マウス中クリック+カーソル移動で平行移動
		if (Novice::IsPressMouse(2)) {

			if (0 < (preMousePos.x - mousePos.x)) {
				cameraPosition.x += 0.1f;
			}

			if (0 > (preMousePos.x - mousePos.x)) {
				cameraPosition.x -= 0.1f;
			}

			if (0 < (preMousePos.y - mousePos.y)) {
				cameraPosition.y -= 0.1f;
			}

			if (0 > (preMousePos.y - mousePos.y)) {
				cameraPosition.y += 0.1f;
			}

		}

		// imGuiによる関数表示

		ImGui::Begin("Setting");
		ImGui::Text("MousePosition(%d,%d)",mousePos.x,mousePos.y);
		ImGui::SliderFloat3("Camera Translate", &cameraPosition.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera Rotate", &cameraRotate.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Camera Scale", &cameraScale.x, 0.1f, 2.0f);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::SliderFloat3("point0", &controlPoints[0].x, -4.0f, 4.0f);
		ImGui::SliderFloat3("point1", &controlPoints[1].x, -4.0f, 4.0f);
		ImGui::SliderFloat3("point2", &controlPoints[2].x, -4.0f, 4.0f);
		ImGui::End();		


		// カメラの更新
		camera->SetWorldAffine(scale, rotate, translate);
		camera->SetCameraAffine(cameraScale, cameraRotate, cameraPosition);
		camera->Update();

		for (int i = 0; i < 3; i++) {
			screenControlPos[i] = camera->GetScreenPos(camera->GetNdcPos(controlPoints[i]));
		}

		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///


		// 描画
		

		// グリッド
		DrawGrid(camera->GetViewprojectionMatrix(), camera->GetViewportMatrix());

		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2],
			camera->GetViewprojectionMatrix(), camera->GetViewportMatrix(), color);

		for (int i = 0; i < 3; i++) {
			Novice::DrawEllipse(
				(int)screenControlPos[i].x, (int)screenControlPos[i].y,
				8, 8, 0.0f, BLUE, kFillModeSolid
			);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete camera;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
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
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	Vector3 cameraPosition = { 0.0f,1.9f,-20.49f };

	// 行列カメラのクラスを宣言・初期化
	MatrixCamera* camera = new MatrixCamera({ kWindowSizeX,kWindowSizeY });
	camera->Initialize();

	// 表示用の変数
	//const int kRowHeight = 30;
	//const int kColumnWidth = 600;

	//
	// 課題用変数　ここから
	//

	// 三角形の座標
	Vector3 kLocalVertices[3];
	kLocalVertices[0] = { 0.0f,2.0f,0.0f };
	kLocalVertices[1] = { 2.0f,0.0f,0.0f };
	kLocalVertices[2] = { -2.0f,0.0f,0.0f };

	Vector3 ndcVertex[3] = {};
	Vector3 screenVertices[3] = {};
	Vector3 cameraFace{};

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	// スクリーン座標系に変換
	for (int i = 0; i < 3; i++) {
		ndcVertex[i] = camera->GetNdcPos(kLocalVertices[i]);
		screenVertices[i] = camera->GetScreenPos(ndcVertex[i]);
	}

	//
	//　課題用変数　ここまで
	//


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// キー入力
		if (keys[DIK_W]) {
			cameraPosition.y += 0.2f;
		}
		if (keys[DIK_S]) {
			cameraPosition.y -= 0.2f;
		}
		if (keys[DIK_A]) {
			cameraPosition.x -= 0.2f;
		}
		if (keys[DIK_D]) {
			cameraPosition.x += 0.2f;
		}


		if (keys[DIK_SPACE]) {
			rotate.y = 0.0f;
		}

		// Y軸回転を行う
		rotate.y += 0.04f;


		// カメラの更新
		camera->SetWorldAffine(scale, rotate, translate);
		camera->SetCameraAffine(cameraScale, cameraRotate, cameraPosition);
		camera->Update();

		// スクリーン座標系に変換
		for (int i = 0; i < 3; i++) {
			ndcVertex[i] = camera->GetNdcPos(kLocalVertices[i]);
			screenVertices[i] = camera->GetScreenPos(ndcVertex[i]);
		}

		Vector3 a, b = {};
		a = { ndcVertex[1].x - ndcVertex[0].x, ndcVertex[1].y - ndcVertex[0].y, ndcVertex[1].z - ndcVertex[0].z };
		b = { ndcVertex[2].x - ndcVertex[1].x, ndcVertex[2].y - ndcVertex[1].y, ndcVertex[2].z - ndcVertex[1].z };
		cameraFace = Matrix4x4Funk::Transform({ 0,0,1 }, camera->GetViewMatrix());


		// imGuiによる関数表示

		float c = Dot(cameraFace, Cross(a, b));

		ImGui::Begin("Debug");
		ImGui::SliderFloat("Cross", &c, -30.0f, 30.0f);
		ImGui::End();





		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///


		// 描画
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		);

		DrawGrid(camera->GetViewprojectionMatrix(), camera->GetViewportMatrix());

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
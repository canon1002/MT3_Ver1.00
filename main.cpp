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
	Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };

	// 行列カメラのクラスを宣言・初期化
	MatrixCamera* camera = new MatrixCamera({ kWindowSizeX,kWindowSizeY });
	camera->Initialize();

	// 表示用の変数
	//const int kRowHeight = 30;
	//const int kColumnWidth = 600;

	//
	// 課題用変数　ここから
	//

	// 球
	Sphere sphere = {
		{0,0,0} ,
		1,
	};

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


		// カメラの更新
		camera->SetWorldAffine(scale, rotate, translate);
		camera->SetCameraAffine(cameraScale, cameraRotate, cameraPosition);
		camera->Update();


		// imGuiによる関数表示

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTransrate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();





		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///


		// 描画

		// グリッド
		DrawGrid(camera->GetViewprojectionMatrix(), camera->GetViewportMatrix());

		// 球体の描画
		DrawSphere(sphere,
			camera->GetViewprojectionMatrix(),
			camera->GetViewportMatrix(),
			0x000000FF
		);

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
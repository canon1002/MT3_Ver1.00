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

	// 球体
	Sphere sphereA = { {0.0f,0.0f,0.0f},2.0f };
	Sphere sphereB = { {4.0f,0.0f,2.0f},1.0f };

	// 球体の色
	uint32_t color = 0xFFFFFFFF;

	Vector3 screenSphereA = camera->GetScreenPos(camera->GetNdcPos(sphereA.center));
	Vector3 screenSphereB = camera->GetScreenPos(camera->GetNdcPos(sphereB.center));

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

		// imGuiによる関数表示

		ImGui::Begin("Camera");
		ImGui::SliderFloat3("Camera Translate", &cameraPosition.x, -30.0f, 30.0f);
		ImGui::SliderFloat3("Camera Rotate", &cameraRotate.x, -3.0f, 3.0f);
		ImGui::SliderFloat3("Camera Scale", &cameraScale.x, 0.01f, 3.0f);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::SliderFloat3("SphereA Center", &sphereA.center.x, -20.0f, 20.0f);
		ImGui::SliderFloat("SphereA Radius", &sphereA.radius, -10.0f, 10.0f);
		ImGui::SliderFloat3("SphereB Center", &sphereB.center.x, -20.0f, 20.0f);
		ImGui::SliderFloat("SphereB Radius", &sphereB.radius, -10.0f, 10.0f);
		ImGui::End();

		// カメラの更新
		camera->SetWorldAffine(scale, rotate, translate);
		camera->SetCameraAffine(cameraScale, cameraRotate, cameraPosition);
		camera->Update();

		// 球体の座標変換
		screenSphereA = camera->GetScreenPos(camera->GetNdcPos(sphereA.center));
		screenSphereB = camera->GetScreenPos(camera->GetNdcPos(sphereB.center));

		// 衝突判定を行い、接触していたら色を赤色に変更
		if (isCollision(sphereA, sphereB) == true)
		{
			color = RED;
		}
		else
		{
			color = WHITE;
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

		
		// 球体の描画
		DrawSphere(sphereA,
			camera->GetViewprojectionMatrix(),
			camera->GetViewportMatrix(),
			color
		);

		DrawSphere(sphereB,
			camera->GetViewprojectionMatrix(),
			camera->GetViewportMatrix(),
			color
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
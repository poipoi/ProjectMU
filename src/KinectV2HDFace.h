#pragma once

#include <array>

#include "ofMain.h"

#include "Kinect.h"
#include "Kinect.Face.h"

#define	FACE_COUNT		(4)

class KinectV2HDFace
{
public:

	struct Status {
		bool isTracking;
		UINT64 trackingID;
		bool isDoneModelBuilding;
		string collectionStateStr;
		string captureStateStr;
		bool isSelected;
	};


	KinectV2HDFace();
	~KinectV2HDFace();

	void setup(void) {
		for (auto &param : faceParams) {
			param.status.isTracking = false;
			param.status.trackingID = 0;
			param.status.collectionStateStr = "";
			param.status.captureStateStr = "";
			param.status.isDoneModelBuilding = false;
			param.status.isSelected = false;
		}

		setupKinect();

		setupColorFrame();
		setupBodyFrame();
		setupHdFaceFrame();
	}

	void update(void) {
		updateColorFrame();
		updateBodyFrame();
		updateHdFaceFrame();
		updateFacePoints();
	}

	void draw(void) {
		drawColorImage();
		drawFacePoints();
	}

	vector<Status> getStatuses(void) {
		vector<Status> statuses;
		for (auto &param : faceParams) {
			statuses.push_back(param.status);
		}
		return statuses; 
	}

	Status getStatus(int i) {
		return faceParams[i].status;
	}

	vector<ofPoint> getPoints(int i) {
		return faceParams[i].points;
	}

	ofImage& getImage(void) {
		return img;
	}

	ofColor getColor(int i) {
		return faceParams[i].color;
	}

	bool isValid(int i) {
		return faceParams[i].status.isTracking;
	}

	void setSelected(array<bool, BODY_COUNT> &isSelectedArr) {
		for (int i = 0; i < BODY_COUNT; i++) {
			faceParams[i].status.isSelected = isSelectedArr[i];
		}
	}

private:

	// ポインタ管理用スマートポインタクラス（CComPtr代用）
	template<class T> class SPtr {
	public:

		SPtr(void) :
			ptr(nullptr)
		{

		}

		~SPtr(void) {
			if (ptr != nullptr) {
				ptr->Release();
			}
		}

		T** operator&(void) { return &ptr; }

		T* operator->(void) { return ptr; }

		bool operator==(T* srcPtr) { return ptr == srcPtr; }
		bool operator!=(T* srcPtr) { return ptr != srcPtr; }
		T* get(void) { return ptr; }

		T *ptr;
	};


	// Kinect Senserの初期化
	void setupKinect(void) {
		// Kinect 初期化
		HRESULT result = GetDefaultKinectSensor(&kinect);
		kinect->Open();

		// Coordinate Map 取得
		kinect->get_CoordinateMapper(&coordinateMapper);
	}

	// Color Frame の初期化
	void setupColorFrame(void) {
		// Color Frame 初期化
		SPtr<IColorFrameSource> colorFrameSource;
		kinect->get_ColorFrameSource(&colorFrameSource);
		colorFrameSource->OpenReader(&colorFrameReader);

		// Color Frame Descripion の取得
		colorFrameSource->CreateFrameDescription(colorFormat, &colorFrameDescription);
		colorFrameDescription->get_Width(&colorWidth);
		colorFrameDescription->get_Height(&colorHeight);
		colorFrameDescription->get_BytesPerPixel(&bytesPerPixel);
	}

	// Body Frame の初期化
	void setupBodyFrame(void)
	{
		// Body Frame 初期化
		SPtr<IBodyFrameSource> bodyFrameSource;
		kinect->get_BodyFrameSource(&bodyFrameSource);
		bodyFrameSource->OpenReader(&bodyFrameReader);
	}

	// HD Face Frame の初期化
	void setupHdFaceFrame(void) {
		// HD Face Frame 初期化
		int i = 0;
		for (auto &param : faceParams) {
			SPtr<IHighDefinitionFaceFrameSource> hdFaceFrameSource;
			CreateHighDefinitionFaceFrameSource(kinect.get(), &hdFaceFrameSource);
			hdFaceFrameSource->OpenReader(&param.reader);

			// Face Alignmentを作成
			CreateFaceAlignment(&param.p_alignment);

			// Face Modelを作成
			CreateFaceModel(1.0f, FaceShapeDeformations::FaceShapeDeformations_Count, &shapeUnits[0], &param.model);
			GetFaceModelVertexCount(&vertexCount);

			// Face Model Builderを作成、開始
			FaceModelBuilderAttributes attribures = FaceModelBuilderAttributes::FaceModelBuilderAttributes_None;
			hdFaceFrameSource->OpenModelBuilder(attribures, &param.builder);
			param.builder->BeginFaceDataCollection();

			// Model作成済み判断用フラグ
			param.status.isDoneModelBuilding = false;

			// 色設定
			param.color = ofColor::fromHsb(float(255) * i / faceParams.size(), 255, 255);
			i++;
		}
	}

	// Color Frame 更新
	void updateColorFrame(void) {
		if (colorFrameReader.get() == nullptr) return;

		// 最新フレームの取得
		SPtr<IColorFrame> colorFrame;
		HRESULT result = colorFrameReader->AcquireLatestFrame(&colorFrame);

		if (FAILED(result)) {
			return;
		}

		// ofImageへの変換
		vector<unsigned char> buff;
		buff.resize(colorWidth * colorHeight * bytesPerPixel);
		colorFrame->CopyConvertedFrameDataToArray(buff.size(), &buff[0], colorFormat);
		img.setFromPixels(&buff[0], colorWidth, colorHeight, OF_IMAGE_COLOR_ALPHA);
		buff.clear();
	}

	// Body Frame 更新
	void updateBodyFrame(void) {
		if (bodyFrameReader.get() == nullptr) return;

		// 最新フレームの更新
		SPtr<IBodyFrame> bodyFrame;
		HRESULT result = bodyFrameReader->AcquireLatestFrame(&bodyFrame);
		if (FAILED(result)) {
			return;
		}

		// Body Data 取得、トラッキングID取得
		bodyFrame->GetAndRefreshBodyData(BODY_COUNT, &bodies[0]);
		trackingCount = 0;


		bool isNormal = true;
		int selectNum = -1;
		for (int i = 0; i < BODY_COUNT; i++) {
			if (faceParams[i].status.isSelected) {
				isNormal = false;
				selectNum = i;
				break;
			}
		}

		for (auto &param : faceParams) {
			param.status.trackingID = 0;
			param.status.isTracking = false;
		}

		if (isNormal) {
			for (int i = 0; i < BODY_COUNT; i++) {
				UINT64 id;
				BOOLEAN isTrack;
				bodies[i]->get_IsTracked(&isTrack);
				if (isTrack) {

					bodies[i]->get_TrackingId(&id);

					faceParams[i].status.trackingID = id;
					faceParams[i].status.isTracking = true;
				}
			}
		}
		else {
			for (int i = 0; i < BODY_COUNT; i++) {
				if (i == selectNum) {
					bool isFound = false;
					UINT64 id;
					for (auto &body : bodies) {
						BOOLEAN isTrack;
						body->get_IsTracked(&isTrack);
						if (isTrack) {
							body->get_TrackingId(&id);

							faceParams[i].status.trackingID = id;
							faceParams[i].status.isTracking = true;
							isFound = true;
							break;
						}
					}
					if (!isFound) {
						faceParams[i].status.trackingID = 0;
						faceParams[i].status.isTracking = false;
					}
				}
				else {
					faceParams[i].status.trackingID = 0;
					faceParams[i].status.isTracking = false;
				}
			}
		}
		
		/*
		for (int i = 0; i < BODY_COUNT; i++) {
			if (trackingCount >= FACE_COUNT) {
				break;
			}

			UINT64 id;
			bodies[i]->get_TrackingId(&id);
			if (id == 0) {
				continue;
			}

			if (isNormal) {
				bool isOK = false;
				for (auto &param : faceParams) {
					if (param.status.trackingID == id) {
						param.status.isTracking = true;
						isOK = true;
						break;
					}
				}

				if (!isOK) {
					for (auto &param : faceParams) {
						if (!param.status.isTracking) {
							param.status.trackingID = id;
							param.status.isTracking = true;
						}
					}
				}
			}
			else {
				faceParams[selectNum].status.trackingID = id;
				faceParams[selectNum].status.isTracking = true;
			}

			trackingCount++;

			if (!isNormal) { break; }
		}

		for (auto &param : faceParams) {
			if (!param.status.isTracking) {
				param.status.trackingID = 0;
			}
		}
		*/
	}

	// HD Face Frame 更新
	void updateHdFaceFrame() {
		for (auto &param : faceParams) {

			// トラッキングIDの登録
			if (param.status.trackingID == 0) {
				continue;
			}
			SPtr<IHighDefinitionFaceFrameSource> hdFaceFrameSource;
			param.reader->get_HighDefinitionFaceFrameSource(&hdFaceFrameSource);

			hdFaceFrameSource->put_TrackingId(param.status.trackingID);

			// HD Face Frame 更新
			SPtr<IHighDefinitionFaceFrame> hdFaceFrame;
			HRESULT result = param.reader->AcquireLatestFrame(&hdFaceFrame);
			if (FAILED(result)) {
				continue;
			}

			// Face Tracking しているかどうか確認
			BOOLEAN isTrackingNow;
			hdFaceFrame->get_IsFaceTracked(&isTrackingNow);
			param.status.isTracking = isTrackingNow;
			if (!isTrackingNow) {
				continue;
			}

			// Face Alignment 取得
			result = hdFaceFrame->GetAndRefreshFaceAlignmentResult(param.p_alignment);
			if (param.p_alignment == nullptr) {
				continue;
			}

			// Face Model 作成
			if (!param.status.isSelected) { continue; }

			if (!param.status.isDoneModelBuilding) {
				// Face Model 未作成の場合
				FaceModelBuilderCollectionStatus collection;
				param.builder->get_CollectionStatus(&collection);

				if (!collection) {
					// コレクション成功の場合、FaceModel作成
					SPtr<IFaceModelData> faceModelData;
					param.builder->GetFaceData(&faceModelData);
					if (faceModelData != nullptr) {
						faceModelData->ProduceFaceModel(&param.model);
					}

					clearCollectionStatus(param.status);
					param.status.isDoneModelBuilding = true;
				}
				else {
					// 状態出力
					updateCollectionStatus(param.builder.get(), collection, param.status);
				}
			}
		}
	}

	// Face Point の更新
	void updateFacePoints(void) {
		for (auto &param : faceParams) {
			if (!param.status.isTracking) {
				param.points.clear();
				continue;
			}

			// Camera Space Point の取得
			vector<CameraSpacePoint> vertices(vertexCount);
			param.model->CalculateVerticesForAlignment(param.p_alignment, vertexCount, &vertices[0]);

			// Color Space Point の取得
			vector<ColorSpacePoint> colorPoints(vertexCount);
			coordinateMapper->MapCameraPointsToColorSpace(vertexCount, &vertices[0], vertexCount, &colorPoints[0]);

			// ofPoint への変換
			param.points.clear();
			for (auto point : colorPoints) {
				param.points.push_back(ofPoint(point.X, point.Y));
			}
		}
	}

	// Color Image 描画
	void drawColorImage(void) {
		if (img.isAllocated()) {
			img.draw(0, 0);
		}
	}

	// Face Points 描画
	void drawFacePoints(void) {
		for (auto &param : faceParams) {
			ofPushStyle();

			ofSetColor(param.color);

			for (auto point : param.points) {
				ofCircle(point, 2);
			}

			ofPopStyle();
		}
	}

	bool isKinectReady(void) {
		BOOLEAN isReady;
		kinect->get_IsOpen(&isReady);
		return isReady == TRUE;
	}

	void clearCollectionStatus(Status &status) {
		status.collectionStateStr = "";
		status.captureStateStr = "";
	}

	void updateCollectionStatus(IFaceModelBuilder *builder, const FaceModelBuilderCollectionStatus &collection, Status &status) {
		if (collection & FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_TiltedUpViewsNeeded){
			status.collectionStateStr = "Need : Tilted Up Views";
		}
		else if (collection & FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_RightViewsNeeded){
			status.collectionStateStr = "Need : Right Views";
		}
		else if (collection & FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_LeftViewsNeeded){
			status.collectionStateStr = "Need : Left Views";
		}
		else if (collection & FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_FrontViewFramesNeeded){
			status.collectionStateStr = "Need : Front ViewFrames";
		}

		FaceModelBuilderCaptureStatus capture;
		builder->get_CaptureStatus(&capture);

		switch (capture){
		case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_FaceTooFar:
			status.captureStateStr = "Error : Face Too Far from Camera";
			break;
		case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_FaceTooNear:
			status.captureStateStr = "Error : Face Too Near to Camera";
			break;
		case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_MovingTooFast:
			status.captureStateStr = "Error : Moving Too Fast";
			break;
		default:
			status.captureStateStr = "";
			break;
		}
	}


	SPtr<IKinectSensor> kinect;
	SPtr<IColorFrameReader> colorFrameReader;
	static const ColorImageFormat colorFormat = ColorImageFormat::ColorImageFormat_Rgba;

	SPtr<IFrameDescription> colorFrameDescription;
	int colorWidth;
	int colorHeight;
	unsigned int bytesPerPixel;

	SPtr<ICoordinateMapper> coordinateMapper;

	SPtr<IBodyFrameReader> bodyFrameReader;

	array<SPtr<IBody>, BODY_COUNT> bodies;

	int trackingCount;

	UINT32 vertexCount;

	std::array<float, FaceShapeDeformations::FaceShapeDeformations_Count> shapeUnits;

	ofImage img;

	struct HDFaceParameter
	{
		SPtr<IHighDefinitionFaceFrameReader> reader;
		IFaceAlignment *p_alignment;
		SPtr<IFaceModel> model;
		SPtr<IFaceModelBuilder> builder;
		vector<ofPoint> points;
		ofColor color;
		Status status;
	};

	array<HDFaceParameter, BODY_COUNT> faceParams;

};


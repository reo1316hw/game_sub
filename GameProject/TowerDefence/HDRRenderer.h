#pragma once

class HDRRenderer
{
public:
	HDRRenderer(int _fbowidth, int _fboheight, int _bloomLevel);
	~HDRRenderer();

	void HdrRecordBegin();
	void HdrRecordEnd();
	void HiBrightBlurCreate();
	void HdrTonemapAndBrightBlurCombine();
	void CopyDepthToScreen();

	unsigned int GetColorTexID()	{ return mHdrColorBuffers[0]; }
	unsigned int GetHDRTexID()		{ return mHdrColorBuffers[1]; }

private:
	void  InitHDRBuffers();
	void  InitBlurBuffers();
	void  InitScreenQuadVAO();
	float GaussianDistribution(const Vector2& _pos, float _rho);
	void  CalcGaussBlurParam(int _w, int _h, Vector2 _dir, float _deviation);

	class Shader*             mGaussianBlurShader;
	class Shader*             mDownSamplingShader;
	class Shader*             mHdrToneAndBlurBlendShader;
	unsigned int              mQuadScreenVAO;
	unsigned int              mQuadScreenVBO;

	unsigned int              mBufferWidth;
	unsigned int              mBufferHeight;
	unsigned int              mBloomBufferLevel;
	unsigned int              mBloomBufferNum;

	unsigned int              mHdrFBO;              // ���������_FBO
	unsigned int              mHdrRBO;
	unsigned int              mHdrColorBuffers[2];

	std::vector<unsigned int> mBlurFBOs;            // �u���[�p�̃t���[���o�b�t�@�I�u�W�F�N�g
	std::vector<unsigned int> mBlurBufferTexs;      // �u���[���ʂ̃e�N�X�`��ID

	const int                 mSampleCount = 15;    // �K�E�X�ڂ����̃T���v�����O�_
	Vector3                   mOffset[15];          // �T���v�����O�_�̍��W(u,v) & w:�d��

};
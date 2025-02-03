//=============================================================
//
// �e�L�X�g�R���|�[�l���g [text.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "text.h"
#include "manager.h"
#include <regex>
#include <thread>

const CText::FontData CText::LoadFonts[] = {
    {"data\\FONT\\ZenKakuGothicNew-Bold.ttf", "Zen Kaku Gothic New"},
    {"data\\FONT\\Tetsubin-Gothic.otf", "07�S�r�S�V�b�N"},
    {"data\\FONT\\LightNovelPOPv2.otf", "���m�xPOP v2"},
};

//=============================================================
// [CText] �t�H���g�̓ǂݍ���
//=============================================================
void CText::InitLoadFont()
{
    std::string sFailedFont = "";
    int nFailedCounter = 0;
    for (int i = 0; i < sizeof(LoadFonts) / sizeof(FontData); i++)
    {
        if (!(AddFontResourceEx(LoadFonts[i].sFontPath.c_str(), FR_PRIVATE, NULL) > 0))
        { // ���s
            if (nFailedCounter > 0)
                sFailedFont += ", ";

            sFailedFont += LoadFonts[i].sFontName;
            nFailedCounter++;
        }
    }
    
    // ���s�����Ƃ�
    if (nFailedCounter > 0)
    {
        sFailedFont = std::to_string(nFailedCounter) + "�̃t�H���g�̓ǂݍ��݂Ɏ��s���܂���" + "\n�t�H���g��: " + sFailedFont;
        MessageBox(nullptr, sFailedFont.c_str(), "�x��", MB_OK | MB_ICONERROR);
    }
}

//=============================================================
// [CText] ������
//=============================================================
void CText::Init()
{
    // �X�v���C�g���쐬����
    if (FAILED(D3DXCreateSprite(CRenderer::GetInstance()->GetDevice(), &m_pSprite)))
    { // ���s��
        std::cout << "���s";
    }

    // �����ݒ�
    m_fontName = "MS �S�V�b�N";
    m_fontSize = 100;
    m_outlineSize = 0;
    m_fMaxHeight = 0.0f;
    m_outlineColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_fillColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_align = ALIGN::LEFT;
    m_alpha = 1.0f;
}

//=============================================================
// [CText] �I��
//=============================================================
void CText::Uninit()
{
    // �e�L�X�g�f�[�^�̔j��
    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        // �t�H���g�e�N�X�`���̔j��
        if (m_textInfos[i].pTex != nullptr)
        {
            m_textInfos[i].pTex->Release();
            m_textInfos[i].pTex = nullptr;
        }
    }
    m_textInfos.clear();

    // �X�v���C�g�̔j��
    if (m_pSprite != nullptr)
    {
        m_pSprite->Release();
        m_pSprite = nullptr;
    }
}

//=============================================================
// [CText] UI�`��
//=============================================================
void CText::DrawUI()
{
    // �X�P�[���Ɖ�]�̃}�g���b�N�X
    D3DXMATRIX mtx, mtxScale, mtxRot;
    D3DXMatrixIdentity(&mtx);
    D3DXMatrixScaling(&mtxScale, transform->GetWScale().x, transform->GetWScale().y, transform->GetWScale().z);
    mtxRot = transform->GetRotationMatrix();
    D3DXMatrixMultiply(&mtx, &mtxScale, &mtxRot);

    // �X�v���C�g�Ƀ}�g���b�N�X��K�p����
    m_pSprite->SetTransform(&mtx);

    m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        D3DXVECTOR3 pos = { transform->GetWPos().x + m_textInfos[i].pos.x, transform->GetWPos().y - m_textInfos[i].pos.y + m_fMaxHeight * m_textInfos[i].line, 0.0f };
        m_pSprite->Draw(m_textInfos[i].pTex, 0, 0, &pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));
    }

    m_pSprite->End();
}

//=============================================================
// [CText] �e�L�X�g�̐ݒ�
//=============================================================
void CText::SetText(const std::string& text)
{
    if (m_text != text)
    {
        m_text = text;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] �t�H���g�T�C�Y�̐ݒ�
//=============================================================
void CText::SetFontSize(const int& size)
{
    if (m_fontSize != size)
    {
        m_fontSize = size;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] �t�H���g���̐ݒ�
//=============================================================
void CText::SetFont(const std::string& fontName)
{
    if (m_fontName != fontName)
    {
        m_fontName = fontName;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] ����̐ݒ�
//=============================================================
void CText::SetAlign(const ALIGN& align)
{
    if (m_align != align)
    {
        m_align = align;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] �����x�̐ݒ�
//=============================================================
void CText::SetAlpha(const float& fAlpha)
{
    m_alpha = fAlpha;
}

//=============================================================
// [CText] �A�E�g���C���T�C�Y�̐ݒ�
//=============================================================
void CText::SetOutlineSize(const int& size)
{
    if (m_outlineSize != size)
    {
        m_outlineSize = size;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] �A�E�g���C���̐F�ݒ�
//=============================================================
void CText::SetOutlineColor(const D3DXCOLOR& color)
{
    if (m_outlineColor != color)
    {
        m_outlineColor = color;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] �t�H���g�̐F�ݒ�
//=============================================================
void CText::SetFontColor(const D3DXCOLOR& color)
{
    if (m_fillColor != color)
    {
        m_fillColor = color;

        // �e�L�X�g�̍X�V
        UpdateText();
    }
}

//=============================================================
// [CText] �e�L�X�g�̍X�V
//=============================================================
void CText::UpdateText()
{
    // ���܂ł̃e�N�X�`����j������
    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        // �t�H���g�e�N�X�`���̔j��
        if (m_textInfos[i].pTex != nullptr)
        {
            m_textInfos[i].pTex->Release();
            m_textInfos[i].pTex = nullptr;
        }
    }
    m_textInfos.clear();
    m_fMaxHeight = 0.0f;

    // �\���e�L�X�g
    std::string sShowText = m_text;

    // �e�L�X�g�^�O
    std::vector<CTextTag*> vecTextTag;

    // �T�C�Y�^�O
    std::regex sizeTag(R"(<size=(\d+)>)");
    std::smatch match;
    auto it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, sizeTag))
    {
        CSizeTag* pSizeTag = new CSizeTag();
        pSizeTag->SetSize(atoi(match.str(1).c_str()));

        pSizeTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pSizeTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // �J���[�^�O
    std::regex colorTag(R"(<color=(\d+),\s?(\d+),\s?(\d+)>)");
    it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, colorTag))
    {
        CColorTag* pColorTag = new CColorTag();
        pColorTag->SetColor(D3DCOLOR_RGBA( atoi(match.str(1).c_str()), atoi(match.str(2).c_str()), atoi(match.str(3).c_str()), 255));

        pColorTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pColorTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // �J���[�^�O�i���Z�b�g�j
    std::regex colorResetTag(R"(<color=reset>)");
    it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, colorResetTag))
    {
        CColorTag* pColorTag = new CColorTag();
        pColorTag->SetFillColor(m_fillColor);
        pColorTag->SetEdgeColor(m_outlineColor);

        pColorTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pColorTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // �t�H���g�J���[�^�O
    std::regex fontColorTag(R"(<font-color=(\d+),\s?(\d+),\s?(\d+)>)");
    it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, fontColorTag))
    {
        CFontColorTag* pFontColorTag = new CFontColorTag();
        pFontColorTag->SetColor(D3DCOLOR_RGBA(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()), atoi(match.str(3).c_str()), 255));

        pFontColorTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pFontColorTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // �t�H���g�J���[�^�O�i���Z�b�g�j
    std::regex fontColorResetTag(R"(<font-color=reset>)");
    it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, fontColorResetTag))
    {
        CFontColorTag* pFontColorTag = new CFontColorTag();
        pFontColorTag->SetColor(m_fillColor);

        pFontColorTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pFontColorTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // �G�b�W�J���[�^�O
    std::regex edgeColorTag(R"(<edge-color=(\d+),\s?(\d+),\s?(\d+)>)");
    it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, edgeColorTag))
    {
        CEdgeColorTag* pEdgeColorTag = new CEdgeColorTag();
        pEdgeColorTag->SetColor(D3DCOLOR_RGBA(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()), atoi(match.str(3).c_str()), 255));

        pEdgeColorTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pEdgeColorTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // �G�b�W�J���[�^�O�i���Z�b�g�j
    std::regex edgeColorResetTag(R"(<edge-color=reset>)");
    it = sShowText.cbegin();
    while (std::regex_search(it, sShowText.cend(), match, edgeColorResetTag))
    {
        CEdgeColorTag* pEdgeColorTag = new CEdgeColorTag();
        pEdgeColorTag->SetColor(m_outlineColor);

        pEdgeColorTag->SetIdx(static_cast<int>(match.position(0)));
        sShowText.erase(match.position(0), match.length());
        vecTextTag.push_back(pEdgeColorTag);

        // �^�O�̈ʒu����
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    int nTextLength = static_cast<int>(sShowText.length());     // ������
    float fTextWidth = 0.0f;
    int fontSize = m_fontSize;
    D3DXCOLOR fillColor = m_fillColor;
    D3DXCOLOR edgeColor = m_outlineColor;
    int lineCounter = 1;
    for (int i = 0; i < nTextLength; i++)
    {
        TextInfo textInfo;
        RECT strInfo;

        // �e�L�X�g�^�O
        for (int n = 0; n < (int)vecTextTag.size(); n++)
        {
            if (vecTextTag[n]->GetIdx() == i)
            {
                if (vecTextTag[n]->GetType() == CTextTag::TYPE::SIZE)
                {
                    CSizeTag* sizeTag = (CSizeTag*)vecTextTag[n];
                    fontSize = sizeTag->GetSize();
                }
                else if (vecTextTag[n]->GetType() == CTextTag::TYPE::COLOR)
                {
                    CColorTag* colorTag = (CColorTag*)vecTextTag[n];
                    fillColor = colorTag->GetFillColor();
                    edgeColor = colorTag->GetEdgeColor();
                }
                else if (vecTextTag[n]->GetType() == CTextTag::TYPE::FONT_COLOR)
                {
                    CFontColorTag* fontColorTag = (CFontColorTag*)vecTextTag[n];
                    fillColor = fontColorTag->GetColor();
                }
                else if (vecTextTag[n]->GetType() == CTextTag::TYPE::EDGE_COLOR)
                {
                    CEdgeColorTag* edgeColorTag = (CEdgeColorTag*)vecTextTag[n];
                    edgeColor = edgeColorTag->GetColor();
                }
            }
        }

        // ����
        const char* pChar = nullptr;
        std::string text;
        if (IsDBCSLeadByte(sShowText[i]))
        { // 2�o�C�g����
            text = sShowText.substr(i, 2);
            pChar = text.c_str();
            i++;
        }
        else
        { // 1�o�C�g����
            text = sShowText.substr(i, 1);
            pChar = text.c_str();
        }

        // ���s
        if (strcmp(&pChar[0], "\n") == 0)
        {
            lineCounter++;
            fTextWidth = 0.0f;
            continue;
        }

        // �t�H���g�e�N�X�`���̐���
        textInfo.pTex = CreateFontTexture(
            m_fontName.c_str(),
            SHIFTJIS_CHARSET,
            pChar,
            fontSize,
            0,
            m_outlineSize,
            edgeColor,
            fillColor,
            3,
            &strInfo
        );

        // �`��ʒu�����߂�
        textInfo.pos = { fTextWidth, (float)strInfo.bottom - (float)strInfo.top, 0.0f };
        textInfo.line = lineCounter;
        fTextWidth += strInfo.right;

        if (m_fMaxHeight < textInfo.pos.y)
        {
            m_fMaxHeight = textInfo.pos.y;
        }

        m_textInfos.push_back(textInfo);
    }

    // ����
    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        if (m_align == ALIGN::CENTER)
        { // ��������
            m_textInfos[i].pos.x -= fTextWidth / 2;
        }
        else if (m_align == ALIGN::RIGHT)
        { // �E����
            m_textInfos[i].pos.x -= fTextWidth;
        }
    }

    // �e�L�X�g�^�O��j������
    for (int i = 0; i < (int)vecTextTag.size(); i++)
    {
        if (vecTextTag[i] != nullptr)
        {
            delete vecTextTag[i];
            vecTextTag[i] = nullptr;
        }
    }
}

//=============================================================
// [CText] �t�H���g�e�N�X�`���̐����i1�����j
//=============================================================
IDirect3DTexture9* CText::CreateFontTexture(
    const char* faceName,
    unsigned char charSet,
    const char* str,
    unsigned fontHeight,
    unsigned weight,
    int penSize,
    D3DXCOLOR edgeColor,
    D3DXCOLOR fillColor,
    int quality,
    RECT* info)
{
    penSize *= quality;
    IDirect3DTexture9* tex = 0;

    // �n���h���ƃf�o�C�X�̎擾
    HWND hWnd = CManager::GetInstance()->GetHWND();
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    // �f�o�C�X�R���e�L�X�g�쐬
    HDC hDC = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);   // ������Ă�����

    // �t�H���g�쐬
    LOGFONTA lf = {};
    lf.lfHeight = fontHeight * quality;    // �g��T�C�Y��
    lf.lfCharSet = charSet;
    lf.lfWeight = weight;
    lf.lfQuality = ANTIALIASED_QUALITY;
    memcpy(lf.lfFaceName, faceName, strlen(faceName));
    HFONT hFont = CreateFontIndirectA(&lf);
    HFONT oldFont = (HFONT)SelectObject(memDC, hFont);     // �t�H���g��ݒ肵�Ȃ��ƃG���[�ɂȂ�܂�

    // �ł�����"��"��`�悷��BMP���쐬
    TEXTMETRICA tm;
    GLYPHMETRICS gm;
    MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
    int len = IsDBCSLeadByte(str[0]) ? 2 : 1;
    UINT code = (len == 2 ? (unsigned char)str[0] << 8 | (unsigned char)str[1] : (unsigned char)str[0]);
    GetTextMetricsA(memDC, &tm);
    GetGlyphOutlineA(memDC, code, GGO_METRICS, &gm, 0, 0, &mat);

    RECT charRegion = {     // LT - RB
            gm.gmptGlyphOrigin.x - penSize / 2,
            tm.tmAscent - gm.gmptGlyphOrigin.y - penSize / 2,
            gm.gmptGlyphOrigin.x + (LONG)gm.gmBlackBoxX + penSize / 2,
            tm.tmAscent - gm.gmptGlyphOrigin.y + (LONG)gm.gmBlackBoxY + penSize / 2
    };

    RECT charWH = { 0, 0, ((LONG)gm.gmBlackBoxX + penSize + quality - 1) / quality * quality, ((LONG)gm.gmBlackBoxY + penSize + quality - 1) / quality * quality };
    int bmpW = charWH.right;
    int bmpH = charWH.bottom;
    BITMAPINFO bmpInfo = {};
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = bmpW;
    bmpInfo.bmiHeader.biHeight = -bmpH;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 24;
    unsigned char* p = 0;
    HBITMAP hBitMap = CreateDIBSection(0, &bmpInfo, DIB_RGB_COLORS, (void**)&p, 0, 0);
    HBITMAP oldBMP = (HBITMAP)SelectObject(memDC, hBitMap);

    // BMP�w�i��F�ŏ�����
    HBRUSH bgBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
    FillRect(memDC, &charWH, bgBrush);
    DeleteObject(bgBrush);

    // �ł�����"��"�̃p�X��`��
    // �p�X�F�͗΁A�h�͐�
    HPEN   hPen = (HPEN)CreatePen(PS_SOLID, penSize, RGB(0, 255, 0));
    HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
    HPEN   oldPen = (HPEN)SelectObject(memDC, hPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

    SetBkMode(memDC, TRANSPARENT);
    BeginPath(memDC);
    TextOutA(memDC, -charRegion.left, -charRegion.top, str, len);
    EndPath(memDC);
    StrokeAndFillPath(memDC);

    SelectObject(memDC, oldPen);
    SelectObject(memDC, oldBrush);
    SelectObject(memDC, oldFont);
    SelectObject(memDC, oldBMP);
    DeleteObject(hBrush);
    DeleteObject(hPen);
    DeleteObject(hFont);

    // DirectX�̃e�N�X�`����BMP�̐F�������g���t�H���g�����
    int texW = charWH.right / quality;
    int texH = charWH.bottom / quality;
    int q2 = quality * quality;
    if (FAILED(pDevice->CreateTexture(texW, texH, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, 0)))
    {
        return nullptr;
    }
    D3DLOCKED_RECT lockR;
    if (SUCCEEDED(tex->LockRect(0, &lockR, 0, 0))) {
        char* d = (char*)lockR.pBits;
        unsigned BMPPitch = (charWH.right * 3 + 3) / 4 * 4;
        for (int y = 0; y < texH; y++) {
            for (int x = 0; x < texW; x++) {
                unsigned& v = *((unsigned*)d + x + y * texW);   // �e�N�X�`���̃s�N�Z���ʒu
                unsigned alph = 0;
                unsigned edge = 0;
                unsigned fill = 0;
                // quality�{�����_�𕽋ω�
                for (int i = 0; i < quality; i++) {
                    for (int j = 0; j < quality; j++) {
                        alph += p[(y * quality + i) * BMPPitch + (x * quality + j) * 3 + 0];
                        edge += p[(y * quality + i) * BMPPitch + (x * quality + j) * 3 + 1];
                        fill += p[(y * quality + i) * BMPPitch + (x * quality + j) * 3 + 2];
                    }
                }
                alph /= q2;
                edge /= q2;
                fill /= q2;

                // �F�̌`���ϊ�
                int colEdge[4] = { (int)(edgeColor.r * 255), (int)(edgeColor.g * 255), (int)(edgeColor.b * 255), (int)(edgeColor.a * 255) };
                int colFill[4] = { (int)(fillColor.r * 255), (int)(fillColor.g * 255), (int)(fillColor.b * 255), (int)(fillColor.a * 255) };

                // �s�����̏ꍇ�̓u�����h�F���̗p
                unsigned a = 0xff - alph;
                if (a < 0xff) {
                    // ������
                    unsigned r = colEdge[0];
                    unsigned g = colEdge[1];
                    unsigned b = colEdge[2];
                    a = (a * colEdge[3]) >> 8;
                    v = a << 24 | r << 16 | g << 8 | b;
                }
                else {
                    // �s����
                    unsigned r = ((colEdge[0] * edge) >> 8) + ((colFill[0] * fill) >> 8);
                    unsigned g = ((colEdge[1] * edge) >> 8) + ((colFill[1] * fill) >> 8);
                    unsigned b = ((colEdge[2] * edge) >> 8) + ((colFill[2] * fill) >> 8);
                    a = ((colEdge[3] * edge) >> 8) + ((colFill[3] * fill) >> 8);
                    v = a << 24 | r << 16 | g << 8 | b;
                }
            }
        }
        tex->UnlockRect(0);
    }

    DeleteObject(hBitMap);
    DeleteDC(memDC);

    if (info) {
        info->left = charRegion.left / quality;
        info->top = charRegion.top / quality;
        info->right = (gm.gmCellIncX + penSize) / quality;
        info->bottom = (tm.tmHeight + penSize) / quality;
    }
    return tex;
}

//=============================================================
// [CTypingText] �R���X�g���N�^
//=============================================================
CTypingText::CTypingText()
{
    m_nTypingSpeed = 30;
    m_nTypingCounter = 0;
    m_nTypingNum = 0;
}

//=============================================================
// [CTypingText] �X�V
//=============================================================
void CTypingText::Update()
{
    m_nTypingCounter--;
    if (m_nTypingCounter <= 0 &&
        m_nTypingNum <= (int)m_textInfos.size())
    {
        m_nTypingNum++;

        // ���Z�b�g
        m_nTypingCounter = m_nTypingSpeed;
    }
}

//=============================================================
// [CTypingText] �`��
//=============================================================
void CTypingText::DrawUI()
{
    m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        if (i < m_nTypingNum)
        {
            D3DXVECTOR3 pos = { transform->GetWPos().x + m_textInfos[i].pos.x, transform->GetWPos().y - m_textInfos[i].pos.y + m_fMaxHeight, 0.0f };
            m_pSprite->Draw(m_textInfos[i].pTex, 0, 0, &pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));
        }
    }

    m_pSprite->End();
}
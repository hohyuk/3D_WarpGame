using namespace Client;

_float Client::_vec3::GetLength() const {
    //_float fLength = this->x * this->x + this->y * this->y + this->z * this->z;
    //return sqrtf(fLength);
    return D3DXVec3Length(this);
}

_float Client::_vec3::GetDistance(const _vec3& vDest) const {
    //_float fLength = (vDest.x - this->x) * (vDest.x - this->x)
    //    + (vDest.y - this->y) * (vDest.y - this->y)
    //    + (vDest.z - this->z) * (vDest.z - this->z);
    //return sqrtf(fLength);
    D3DXVECTOR3 vTemp = (const D3DXVECTOR3&)vDest - *(D3DXVECTOR3*)this;
    return D3DXVec3Length(&vTemp);
}

_float Client::_vec3::GetAngle(_vec3* vDest, const bool& isDegree) const {
    D3DXVECTOR3 vTempSrc, vTempDst;
    D3DXVec3Normalize(&vTempSrc, this);
    D3DXVec3Normalize(&vTempDst, vDest);
    if (isDegree)
        return D3DXToDegree(D3DXVec3Dot(&vTempSrc, &vTempDst));
    else
        return D3DXVec3Dot(&vTempSrc, &vTempDst);
}

inline _vec3 Client::_vec3::Normalize() {
    //_float fLength = GetLength();
    //*this /= fLength;
    //return *this;
    return *D3DXVec3Normalize(this, this);
}

inline _float Client::_vec3::Dot(const _vec3* vDest) const {
    //_float fDot = this->x * vDest->x + this->y * vDest->y + this->z * vDest->z;
    //return fDot;
    return D3DXVec3Dot(this, vDest);
}

inline _vec3 Client::_vec3::Cross(const _vec3* vDest) const {
    //_vec3 vCross;
    //vCross.x = this->y * vDest->z - this->z * vDest->y;
    //vCross.y = this->z * vDest->x - this->x * vDest->z;
    //vCross.z = this->x * vDest->y - this->y * vDest->x;
    //return vCross;
    return *D3DXVec3Cross(nullptr, this, vDest);
}

inline _vec3* Client::_vec3::TransformNormal(_matrix* matTrans) {
    //_vec4 vTemp = { this->x, this->y, this->z , 0.f };
    //_matrix matTemp;
    //ZeroMemory(&matTemp, sizeof(_matrix));
    //for (size_t i = 0; i < 4; i++) {
    //    matTemp.m[i][i] = vTemp[i];
    //}
    //matTemp *= *matTrans;
    //for (size_t i = 0; i < 4; i++) {
    //    vTemp[i] = 0;
    //    for (size_t j = 0; j < 4; j++) {
    //        vTemp[i] += matTemp.m[j][i];
    //    }
    //}
    //for (size_t i = 0; i < 3; i++) {
    //    (*this)[i] = vTemp[i];
    //}
    //return this;
    return (_vec3*)D3DXVec3TransformNormal(this, this, matTrans);
}

inline _vec3* Client::_vec3::TransformCoord(_matrix* matTrans) {
    //_vec4 vTemp = { this->x, this->y, this->z , 1.f };
    //_matrix matTemp;
    //ZeroMemory(&matTemp, sizeof(_matrix));
    //for (size_t i = 0; i < 4; i++) {
    //    matTemp.m[i][i] = vTemp[i];
    //}
    //matTemp *= *matTrans;
    //for (size_t i = 0; i < 4; i++) {
    //    vTemp[i] = 0;
    //    for (size_t j = 0; j < 4; j++) {
    //        vTemp[i] += matTemp.m[j][i];
    //    }
    //}
    //for (size_t i = 0; i < 3; i++) {
    //    (*this)[i] = vTemp[i];
    //}
    //return *this;
    return (_vec3*)D3DXVec3TransformCoord(this, this, matTrans);
}

//_vec3 Client::_vec3::GetVec3FromAngleZ(_float angle, const bool& isDegree) {
//    if (isDegree) angle = D3DXToRadian(angle);
//    return { cosf(angle), sinf(angle), 0.f };
//}

inline _matrix* Client::_matrix::SetIdentity() {
    return (_matrix*)D3DXMatrixIdentity(this);
        // this->m[0][1] = this->m[0][2] = this->m[0][3] =
        //     this->m[1][0] = this->m[1][2] = this->m[1][3] =
        //     this->m[2][0] = this->m[2][1] = this->m[2][3] =
        //     this->m[3][0] = this->m[3][1] = this->m[3][2] = 0.0f;

        // this->m[0][0] = this->m[1][1] = this->m[2][2] = this->m[3][3] = 1.0f;
        // return this;
}

inline _matrix* Client::_matrix::Scaling(const _float& x, const _float& y, const _float& z) {
    D3DXMatrixScaling(this, x, y, z);
    return this;
}

inline _matrix* Client::_matrix::Scaling(const _vec3& vScale) {
    D3DXMatrixScaling(this, vScale.x, vScale.y, vScale.z);
    return this;
}

inline _matrix* Client::_matrix::Translation(const _float& x, const _float& y, const _float& z) {
    return (_matrix*)D3DXMatrixTranslation(this, x, y, z);
    // this->m[0][1] = this->m[0][2] = this->m[0][3] =
    //     this->m[1][0] = this->m[1][2] = this->m[1][3] =
    //     this->m[2][0] = this->m[2][1] = this->m[2][3] = 0.0f;

    // this->m[3][0] = x;
    // this->m[3][1] = y;
    // this->m[3][2] = z;

    // this->m[0][0] = this->m[1][1] = this->m[2][2] = this->m[3][3] = 1.0f;
    // return this;
}

inline _matrix* Client::_matrix::Translation(const _vec3& vTrans) {
    return (_matrix*)D3DXMatrixTranslation(this, vTrans.x, vTrans.y, vTrans.z);
    // this->m[0][1] = this->m[0][2] = this->m[0][3] =
    //     this->m[1][0] = this->m[1][2] = this->m[1][3] =
    //     this->m[2][0] = this->m[2][1] = this->m[2][3] = 0.0f;

    // this->m[3][0] = vTrans.x;
    // this->m[3][1] = vTrans.y;
    // this->m[3][2] = vTrans.z;

    // this->m[0][0] = this->m[1][1] = this->m[2][2] = this->m[3][3] = 1.0f;
    // return this;
}

inline _matrix* Client::_matrix::LookAt(const _vec3* pLook, const _vec3* pUp) {
    _vec3 nLook, nUp, nRight;
    D3DXVec3Normalize(&nLook, pLook);
    D3DXVec3Normalize(&nUp, pUp);

    D3DXVec3Cross(&nRight, &nUp, &nLook);
    D3DXVec3Normalize(&nRight, &nRight);
    D3DXVec3Cross(&nUp, &nLook, &nRight);
    this->SetIdentity();
    this->m[0][0] = nRight.x; this->m[0][1] = nRight.y; this->m[0][2] = nRight.z;
    this->m[1][0] = nUp.x;    this->m[1][1] = nUp.y;    this->m[1][2] = nUp.z;
    this->m[2][0] = nLook.x;  this->m[2][1] = nLook.y;  this->m[2][2] = nLook.z;
    return this;
}

inline _matrix* Client::_matrix::LookAtLH(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp) {
    return (_matrix*)D3DXMatrixLookAtLH(this, pEye, pAt, pUp);
}

inline _matrix* Client::_matrix::PerspectiveFovLH(const _float& fovY, const _float& aspect, const _float& zn, const _float& zf) {
    //_float scaleY = 1.f / tanf(fovY / 2.f);
    //_float scaleX = scaleY / aspect;


    //this->m[0][1] = this->m[0][2] = this->m[0][3] =
    //    this->m[1][0] = this->m[1][2] = this->m[1][3] =
    //    this->m[2][0] = this->m[2][1] =
    //    this->m[3][0] = this->m[3][1] = this->m[3][3] = 0.0f;


    //this->m[0][0] = scaleX;
    //this->m[1][1] = scaleY;
    //this->m[2][2] = zf / (zf - zn);
    //this->m[2][3] = 1.f;
    //this->m[3][2] = -zn * zf / (zf - zn);

    //return this;
    return (_matrix*)D3DXMatrixPerspectiveFovLH(this, fovY, aspect, zn, zf);
}


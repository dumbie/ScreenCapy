//Box filter
float4 TextureFilterBox(Texture2D _texture2D, SamplerState _samplerState, float2 texCoord, float2 texSize)
{
    float2 pixel = texCoord * texSize - 0.5F;
    float2 floorpx = floor(pixel);
    float2 fracpx = frac(pixel);

    //Set positions
    float2 posTopLeft = (floorpx + float2(0.0F, 0.0F) + 0.5F) / texSize;
    float2 posTopRight = (floorpx + float2(1.0F, 0.0F) + 0.5F) / texSize;
    float2 posBottomLeft = (floorpx + float2(0.0F, 1.0F) + 0.5F) / texSize;
    float2 posBottomRight = (floorpx + float2(1.0F, 1.0F) + 0.5F) / texSize;

    //Sample texture
    float4 topLeft = _texture2D.Sample(_samplerState, posTopLeft);
    float4 topRight = _texture2D.Sample(_samplerState, posTopRight);
    float4 bottomLeft = _texture2D.Sample(_samplerState, posBottomLeft);
    float4 bottomRight = _texture2D.Sample(_samplerState, posBottomRight);

    //Average
    return (topLeft + topRight + bottomLeft + bottomRight) / 4.0F;
}

//Bilinear filter
float4 TextureFilterBilinear(Texture2D _texture2D, SamplerState _samplerState, float2 texCoord, float2 texSize)
{
    float2 pixel = texCoord * texSize - 0.5F;
    float2 floorpx = floor(pixel);
    float2 fracpx = frac(pixel);

    //Set positions
    float2 posTopLeft = (floorpx + float2(0.0F, 0.0F) + 0.5F) / texSize;
    float2 posTopRight = (floorpx + float2(1.0F, 0.0F) + 0.5F) / texSize;
    float2 posBottomLeft = (floorpx + float2(0.0F, 1.0F) + 0.5F) / texSize;
    float2 posBottomRight = (floorpx + float2(1.0F, 1.0F) + 0.5F) / texSize;

    //Sample texture
    float4 topLeft = _texture2D.Sample(_samplerState, posTopLeft);
    float4 topRight = _texture2D.Sample(_samplerState, posTopRight);
    float4 bottomLeft = _texture2D.Sample(_samplerState, posBottomLeft);
    float4 bottomRight = _texture2D.Sample(_samplerState, posBottomRight);

    //Horizontal interpolation
    float4 combinedTop = lerp(topLeft, topRight, fracpx.x);
    float4 combinedBottom = lerp(bottomLeft, bottomRight, fracpx.x);

    //Vertical interpolation
    return lerp(combinedTop, combinedBottom, fracpx.y);
}
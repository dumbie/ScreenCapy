float3 ColorSrgbToLinear(float3 color)
{
    float3 colorRGB = color.rgb;
    return colorRGB * (colorRGB * (colorRGB * 0.305306011F + 0.682171111F) + 0.012522878F);
}

float3 ColorLinearToSrgb(float3 color)
{
    float3 colorRGB = color.rgb;
    float3 S1 = sqrt(colorRGB);
    float3 S2 = sqrt(S1);
    float3 S3 = sqrt(S2);
    return 0.662002687F * S1 + 0.684122060F * S2 - 0.323583601F * S3 - 0.0225411470F * colorRGB;
}

float ColorLinearToST2084(float color)
{
    float colorPow = pow(abs(color), 0.1593017578F);
    return pow((0.8359375F + 18.8515625F * colorPow) / (1.0F + 18.6875F * colorPow), 78.84375F);
}

float ColorST2084ToLinear(float color)
{
    float colorPow = pow(abs(color), 1.0F / 78.84375F);
    return pow(abs(max(colorPow - 0.8359375F, 0.0F) / (18.8515625F - 18.6875F * colorPow)), 1.0F / 0.1593017578F);
}

float3 ColorHDRtoSDR(float4 color, float sdrWhiteLevel, float hdrPaperWhite, float hdrBrightness)
{
    //Get color rgb
    float3 colorRGB = color.rgb;

    //Adjust SDR white level and HDR paper white
    colorRGB /= (sdrWhiteLevel / hdrPaperWhite);

    //Calculate luminance
    float luminance = max(max(colorRGB.r, colorRGB.g), colorRGB.b);

    //Adjust HDR saturation
    colorRGB = lerp(luminance, colorRGB, 0.98F);

    //Adjust HDR brightness
    colorRGB /= 1.0F + (luminance / hdrBrightness);

    //Convert Linear to SRGB
    colorRGB = ColorLinearToSrgb(colorRGB);

    //Return result
    return colorRGB;
}
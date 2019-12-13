//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests for Counter Scheduler
//==============================================================================

// clang-format off

#include "CounterGeneratorTests.h"
#include "GPASplitCountersInterfaces.h"

#include "GPACounter.h"

#ifdef _WIN32
    #include "counters/PublicDerivedCountersDX11Gfx8.h"
    #include "counters/PublicDerivedCountersDX11Gfx9.h"

    #include "GPAHWCounterDX11Gfx8.h"
    #include "GPAHWCounterDX11Gfx9.h"

    #include "counters/PublicDerivedCountersDX12Gfx8.h"
    #include "counters/PublicDerivedCountersDX12Gfx9.h"

    #include "GPAHWCounterDX12Gfx8.h"
    #include "GPAHWCounterDX12Gfx9.h"
#endif

#include "counters/PublicDerivedCountersGLGfx8.h"
#include "counters/PublicDerivedCountersCLGfx8.h"
#include "counters/PublicDerivedCountersCLGfx9.h"

#define MakeExpectedCounterLocationEntry(x, y) {expectedCountersPass##x[y], MakeLocation(x, y)},

GPA_CounterResultLocation MakeLocation(gpa_uint16 pass, gpa_uint16 offset)
{
    GPA_CounterResultLocation location;
    location.m_pass   = pass;
    location.m_offset = offset;

    return location;
}

#if defined(WIN32) || (defined(_LINUX) && defined(X64))

// Test the openCL counter names on VI hardware
TEST(CounterDLLTests, OpenCLCounterSchedulingVI)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyPassCount(GPA_API_OPENCL, gDevIdVI, FALSE, counters, 1);
}

// Counters to enable (Wavefronts, VALUInsts, SALUInsts, VFetchInsts, SFetchInsts, VWriteInsts, VALUUtilization, VALUBusy, SALUBusy)
TEST(CounterDLLTests, OpenCLResultLocations)
{
    #pragma region Gfx8
    {
        std::vector<unsigned int> counters =
        {
            WavefrontsPublicCLGfx8,
            VALUInstsPublicCLGfx8,
            SALUInstsPublicCLGfx8,
            VFetchInstsPublicCLGfx8,
            SFetchInstsPublicCLGfx8,
            VWriteInstsPublicCLGfx8,
            VALUUtilizationPublicCLGfx8,
            VALUBusyPublicCLGfx8,
            SALUBusyPublicCLGfx8,
        };

        std::vector<uint32_t> expectedCountersPass0 = {3455, 5954, 6073, 6192, 6311, 6430, 6549, 6668, 6787, 6906, 7025, 7144, 7263, 7382,
                                                       7501, 7620, 7739, 3431, 3454, 5955, 6074, 6193, 6312, 6431, 6550, 6669, 6788, 6907,
                                                       7026, 7145, 7264, 7383, 7502, 7621, 7740, 3453, 3457, 3458, 3516, 3508, 2633
                                                      };

        std::vector<uint32_t> expectedCountersPass1 = {3513, 2633};

        std::vector<std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsWavefronts{MakeExpectedCounterLocationEntry(0, 17)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVALUInsts{MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 35)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsSALUInsts{MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 36)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVFetchInsts
        {
            MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 2) MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 5) MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7)
            MakeExpectedCounterLocationEntry(0, 8) MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10)
            MakeExpectedCounterLocationEntry(0, 11) MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 14) MakeExpectedCounterLocationEntry(0, 15) MakeExpectedCounterLocationEntry(0, 16)
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsSFetchInsts{MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 37)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVWriteInsts
        {
            MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 18) MakeExpectedCounterLocationEntry(0, 19)
            MakeExpectedCounterLocationEntry(0, 20) MakeExpectedCounterLocationEntry(0, 21) MakeExpectedCounterLocationEntry(0, 22)
            MakeExpectedCounterLocationEntry(0, 23) MakeExpectedCounterLocationEntry(0, 24) MakeExpectedCounterLocationEntry(0, 25)
            MakeExpectedCounterLocationEntry(0, 26) MakeExpectedCounterLocationEntry(0, 27) MakeExpectedCounterLocationEntry(0, 28)
            MakeExpectedCounterLocationEntry(0, 29) MakeExpectedCounterLocationEntry(0, 30) MakeExpectedCounterLocationEntry(0, 31)
            MakeExpectedCounterLocationEntry(0, 32) MakeExpectedCounterLocationEntry(0, 33) MakeExpectedCounterLocationEntry(0, 34)
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVALUUtilization{MakeExpectedCounterLocationEntry(0, 39)
                MakeExpectedCounterLocationEntry(0, 38)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVALUBusy{MakeExpectedCounterLocationEntry(0, 40) MakeExpectedCounterLocationEntry(0, 39)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsSALUBusy{MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(1, 0)};

        std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
        {
            {WavefrontsPublicCLGfx8, expectedLocationsWavefronts},
            {VALUInstsPublicCLGfx8, expectedLocationsVALUInsts},
            {SALUInstsPublicCLGfx8, expectedLocationsSALUInsts},
            {VFetchInstsPublicCLGfx8, expectedLocationsVFetchInsts},
            {SFetchInstsPublicCLGfx8, expectedLocationsSFetchInsts},
            {VWriteInstsPublicCLGfx8, expectedLocationsVWriteInsts},
            {VALUUtilizationPublicCLGfx8, expectedLocationsVALUUtilization},
            {VALUBusyPublicCLGfx8, expectedLocationsVALUBusy},
            {SALUBusyPublicCLGfx8, expectedLocationsSALUBusy}
        };

        VerifyCountersInPass(GPA_API_OPENCL, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion

    #pragma region Gfx9
    {
        std::vector<unsigned int> counters =
        {
            WavefrontsPublicCLGfx9,
            VALUInstsPublicCLGfx9,
            SALUInstsPublicCLGfx9,
            VFetchInstsPublicCLGfx9,
            SFetchInstsPublicCLGfx9,
            VWriteInstsPublicCLGfx9,
            VALUUtilizationPublicCLGfx9,
            VALUBusyPublicCLGfx9,
            SALUBusyPublicCLGfx9,
        };

        // Pass: 0  Counters: 41
        std::vector<uint32_t> expectedCountersPass0 =
        {
            4217, 7490, 7609, 7728, 7847, 7966, 8085, 8204, 8323, 8442,
            8561, 8680, 8799, 8918, 9037, 9156, 9275, 4193, 4216, 7491,
            7610, 7729, 7848, 7967, 8086, 8205, 8324, 8443, 8562, 8681,
            8800, 8919, 9038, 9157, 9276, 4215, 4219, 4220, 4274, 4260,
            1775
        };

        // Pass: 1  Counters: 2
        std::vector<uint32_t> expectedCountersPass1 =
        {
            4273, 1775
        };

        std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
        };

        // Result locations (Pass, Offset)

        // Pass: 0  Counters: 0
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
        {
            MakeExpectedCounterLocationEntry(0, 17)
        };

        // Pass: 1  Counters: 1
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
        {
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 35)
        };

        // Pass: 2  Counters: 2
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
        {
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 36)
        };

        // Pass: 3  Counters: 3
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations3
        {
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 7)
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 9)
            MakeExpectedCounterLocationEntry(0, 10)
            MakeExpectedCounterLocationEntry(0, 11)
            MakeExpectedCounterLocationEntry(0, 12)
            MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 14)
            MakeExpectedCounterLocationEntry(0, 15)
            MakeExpectedCounterLocationEntry(0, 16)
        };

        // Pass: 4  Counters: 4
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations4
        {
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 37)
        };

        // Pass: 5  Counters: 5
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations5
        {
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 18)
            MakeExpectedCounterLocationEntry(0, 19)
            MakeExpectedCounterLocationEntry(0, 20)
            MakeExpectedCounterLocationEntry(0, 21)
            MakeExpectedCounterLocationEntry(0, 22)
            MakeExpectedCounterLocationEntry(0, 23)
            MakeExpectedCounterLocationEntry(0, 24)
            MakeExpectedCounterLocationEntry(0, 25)
            MakeExpectedCounterLocationEntry(0, 26)
            MakeExpectedCounterLocationEntry(0, 27)
            MakeExpectedCounterLocationEntry(0, 28)
            MakeExpectedCounterLocationEntry(0, 29)
            MakeExpectedCounterLocationEntry(0, 30)
            MakeExpectedCounterLocationEntry(0, 31)
            MakeExpectedCounterLocationEntry(0, 32)
            MakeExpectedCounterLocationEntry(0, 33)
            MakeExpectedCounterLocationEntry(0, 34)
        };

        // Pass: 6  Counters: 10
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations6
        {
            MakeExpectedCounterLocationEntry(0, 39)
            MakeExpectedCounterLocationEntry(0, 38)
        };

        // Pass: 7  Counters: 11
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations7
        {
            MakeExpectedCounterLocationEntry(0, 40)
            MakeExpectedCounterLocationEntry(0, 39)
        };

        // Pass: 8  Counters: 12
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations8
        {
            MakeExpectedCounterLocationEntry(1, 1)
            MakeExpectedCounterLocationEntry(1, 0)
        };

        std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
        {
            { WavefrontsPublicCLGfx9, expectedLocations0 },
            { VALUInstsPublicCLGfx9, expectedLocations1 },
            { SALUInstsPublicCLGfx9, expectedLocations2 },
            { VFetchInstsPublicCLGfx9, expectedLocations3 },
            { SFetchInstsPublicCLGfx9, expectedLocations4 },
            { VWriteInstsPublicCLGfx9, expectedLocations5 },
            { VALUUtilizationPublicCLGfx9, expectedLocations6 },
            { VALUBusyPublicCLGfx9, expectedLocations7 },
            { SALUBusyPublicCLGfx9, expectedLocations8 }
        };

        VerifyCountersInPass(GPA_API_OPENCL, gDevIdGfx9, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}
#endif

TEST(CounterDLLTests, OpenGLCounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(GPUTimePublicGLGfx8);
    counters.push_back(GPUBusyPublicGLGfx8);
    counters.push_back(TessellatorBusyPublicGLGfx8);
    VerifyPassCount(GPA_API_OPENGL, gDevIdVI, FALSE, counters, 2);
}

#ifdef _WIN32

TEST(CounterDLLTests, DX11CounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(GPUTimePublicDX11Gfx8);
    counters.push_back(GPUBusyPublicDX11Gfx8);
    counters.push_back(TessellatorBusyPublicDX11Gfx8);
    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdVI, FALSE, counters, 2);
}


TEST(CounterDLLTests, DX11Gfx8BusyCounters)
{
    #pragma region Gfx8
    {
        std::vector<unsigned int> counters =
        {
            VSBusyPublicDX11Gfx8,
            HSBusyPublicDX11Gfx8,
            DSBusyPublicDX11Gfx8,
            GSBusyPublicDX11Gfx8,
            PSBusyPublicDX11Gfx8,
            CSBusyPublicDX11Gfx8
        };

        std::vector<uint32_t> expectedCountersPass0 = {13056, 13253, 13450, 13647, 13081, 13278, 13475, 13672, 13103, 13300, 13497, 13694, 13125,
                                                       13322, 13519, 13716, 13065, 13262, 13459, 13656, 13087, 13284, 13481, 13678, 10620
                                                      };

        std::vector<uint32_t> expectedCountersPass1 = {13056, 13253, 13450, 13647, 13081, 13278, 13475, 13672, 13125, 13322, 13519, 13716, 13087,
                                                       13284, 13481, 13678, 13109, 13306, 13503, 13700, 10620, 13130, 13327, 13524, 13721
                                                      };

        std::vector<uint32_t> expectedCountersPass2 = {13113, 13310, 13507, 13704, 13117, 13314, 13511, 13708, 13119, 13316, 13513, 13710, 13123,
                                                       13320, 13517, 13714, 10620, 13093, 13290, 13487, 13684, 13099, 13296, 13493, 13690
                                                      };

        std::vector<uint32_t> expectedCountersPass3 = {13072, 13269, 13466, 13663, 13075, 13272, 13469, 13666, 10620};

        std::vector<std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
            expectedCountersPass2,
            expectedCountersPass3,
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVSBusy
        {
            MakeExpectedCounterLocationEntry(0, 24) MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 16)
            MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 20) MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(1, 16) MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 5) MakeExpectedCounterLocationEntry(0, 21)
            MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(1, 17) MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 2) MakeExpectedCounterLocationEntry(0, 18) MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 22) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(1, 18)
            MakeExpectedCounterLocationEntry(0, 14) MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 19)
            MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 23) MakeExpectedCounterLocationEntry(0, 11)
            MakeExpectedCounterLocationEntry(1, 19) MakeExpectedCounterLocationEntry(0, 15)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsHSBusy
        {
            MakeExpectedCounterLocationEntry(2, 16) MakeExpectedCounterLocationEntry(2, 17) MakeExpectedCounterLocationEntry(2, 21)
            MakeExpectedCounterLocationEntry(2, 18) MakeExpectedCounterLocationEntry(2, 22) MakeExpectedCounterLocationEntry(2, 19)
            MakeExpectedCounterLocationEntry(2, 23) MakeExpectedCounterLocationEntry(2, 20) MakeExpectedCounterLocationEntry(2, 24)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsDSBusy
        {
            MakeExpectedCounterLocationEntry(1, 20) MakeExpectedCounterLocationEntry(1, 0) MakeExpectedCounterLocationEntry(1, 4)
            MakeExpectedCounterLocationEntry(1, 12) MakeExpectedCounterLocationEntry(1, 16) MakeExpectedCounterLocationEntry(1, 8)
            MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(1, 5) MakeExpectedCounterLocationEntry(1, 13)
            MakeExpectedCounterLocationEntry(1, 17) MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 2)
            MakeExpectedCounterLocationEntry(1, 6) MakeExpectedCounterLocationEntry(1, 14) MakeExpectedCounterLocationEntry(1, 18)
            MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 3) MakeExpectedCounterLocationEntry(1, 7)
            MakeExpectedCounterLocationEntry(1, 15) MakeExpectedCounterLocationEntry(1, 19) MakeExpectedCounterLocationEntry(1, 11)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsGSBusy
        {
            MakeExpectedCounterLocationEntry(3, 8) MakeExpectedCounterLocationEntry(3, 0) MakeExpectedCounterLocationEntry(3, 4)
            MakeExpectedCounterLocationEntry(3, 1) MakeExpectedCounterLocationEntry(3, 5) MakeExpectedCounterLocationEntry(3, 2)
            MakeExpectedCounterLocationEntry(3, 6) MakeExpectedCounterLocationEntry(3, 3) MakeExpectedCounterLocationEntry(3, 7)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsPSBusy
        {
            MakeExpectedCounterLocationEntry(1, 20) MakeExpectedCounterLocationEntry(1, 8) MakeExpectedCounterLocationEntry(1, 21)
            MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 22) MakeExpectedCounterLocationEntry(1, 10)
            MakeExpectedCounterLocationEntry(1, 23) MakeExpectedCounterLocationEntry(1, 11) MakeExpectedCounterLocationEntry(1, 24)};

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsCSBusy
        {
            MakeExpectedCounterLocationEntry(2, 16) MakeExpectedCounterLocationEntry(2, 0) MakeExpectedCounterLocationEntry(2, 4)
            MakeExpectedCounterLocationEntry(2, 8) MakeExpectedCounterLocationEntry(2, 12) MakeExpectedCounterLocationEntry(2, 1)
            MakeExpectedCounterLocationEntry(2, 5) MakeExpectedCounterLocationEntry(2, 9) MakeExpectedCounterLocationEntry(2, 13)
            MakeExpectedCounterLocationEntry(2, 2) MakeExpectedCounterLocationEntry(2, 6) MakeExpectedCounterLocationEntry(2, 10)
            MakeExpectedCounterLocationEntry(2, 14) MakeExpectedCounterLocationEntry(2, 3) MakeExpectedCounterLocationEntry(2, 7)
            MakeExpectedCounterLocationEntry(2, 11) MakeExpectedCounterLocationEntry(2, 15)};

        std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
        {
            {VSBusyPublicDX11Gfx8, expectedLocationsVSBusy},
            {HSBusyPublicDX11Gfx8, expectedLocationsHSBusy},
            {DSBusyPublicDX11Gfx8, expectedLocationsDSBusy},
            {GSBusyPublicDX11Gfx8, expectedLocationsGSBusy},
            {PSBusyPublicDX11Gfx8, expectedLocationsPSBusy},
            {CSBusyPublicDX11Gfx8, expectedLocationsCSBusy}
        };

        VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}

TEST(CounterDLLTests, DX11Gfx9BusyCounters)
{
    #pragma region Gfx9
    {
        std::vector<unsigned int> counters =
        {
            VSBusyPublicDX11Gfx9,
            HSBusyPublicDX11Gfx9,
            GSBusyPublicDX11Gfx9,
            PSBusyPublicDX11Gfx9,
            CSBusyPublicDX11Gfx9
        };

        // Pass: 0  Counters: 25
        std::vector<uint32_t> expectedCountersPass0 =
        {
            16643, 16839, 17035, 17231, 16647, 16843, 17039, 17235, 16649, 16845,
            17041, 17237, 16653, 16849, 17045, 17241, 23, 16602, 16798, 16994,
            17190, 16611, 16807, 17003, 17199
        };

        // Pass: 1  Counters: 25
        std::vector<uint32_t> expectedCountersPass1 =
        {
            16633, 16829, 17025, 17221, 16639, 16835, 17031, 17227, 23, 16621,
            16817, 17013, 17209, 16624, 16820, 17016, 17212, 16655, 16851, 17047,
            17243, 16660, 16856, 17052, 17248
        };

        std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
        };


        // Result locations (Pass, Offset)

        // Pass: 0  Counters: 5
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
        {
            MakeExpectedCounterLocationEntry(0, 16)
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 21)
            MakeExpectedCounterLocationEntry(0, 18)
            MakeExpectedCounterLocationEntry(0, 22)
            MakeExpectedCounterLocationEntry(0, 19)
            MakeExpectedCounterLocationEntry(0, 23)
            MakeExpectedCounterLocationEntry(0, 20)
            MakeExpectedCounterLocationEntry(0, 24)
        };

        // Pass: 1  Counters: 8
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
        {
            MakeExpectedCounterLocationEntry(1, 8)
            MakeExpectedCounterLocationEntry(1, 0)
            MakeExpectedCounterLocationEntry(1, 4)
            MakeExpectedCounterLocationEntry(1, 1)
            MakeExpectedCounterLocationEntry(1, 5)
            MakeExpectedCounterLocationEntry(1, 2)
            MakeExpectedCounterLocationEntry(1, 6)
            MakeExpectedCounterLocationEntry(1, 3)
            MakeExpectedCounterLocationEntry(1, 7)
        };

        // Pass: 2  Counters: 11
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
        {
            MakeExpectedCounterLocationEntry(1, 8)
            MakeExpectedCounterLocationEntry(1, 9)
            MakeExpectedCounterLocationEntry(1, 13)
            MakeExpectedCounterLocationEntry(1, 10)
            MakeExpectedCounterLocationEntry(1, 14)
            MakeExpectedCounterLocationEntry(1, 11)
            MakeExpectedCounterLocationEntry(1, 15)
            MakeExpectedCounterLocationEntry(1, 12)
            MakeExpectedCounterLocationEntry(1, 16)
        };

        // Pass: 3  Counters: 14
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations3
        {
            MakeExpectedCounterLocationEntry(1, 8)
            MakeExpectedCounterLocationEntry(1, 17)
            MakeExpectedCounterLocationEntry(1, 21)
            MakeExpectedCounterLocationEntry(1, 18)
            MakeExpectedCounterLocationEntry(1, 22)
            MakeExpectedCounterLocationEntry(1, 19)
            MakeExpectedCounterLocationEntry(1, 23)
            MakeExpectedCounterLocationEntry(1, 20)
            MakeExpectedCounterLocationEntry(1, 24)
        };

        // Pass: 4  Counters: 17
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations4
        {
            MakeExpectedCounterLocationEntry(0, 16)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 12)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 9)
            MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 10)
            MakeExpectedCounterLocationEntry(0, 14)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 7)
            MakeExpectedCounterLocationEntry(0, 11)
            MakeExpectedCounterLocationEntry(0, 15)
        };

        std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
        {
            {VSBusyPublicDX11Gfx9, expectedLocations0},
            {HSBusyPublicDX11Gfx9, expectedLocations1},
            {GSBusyPublicDX11Gfx9, expectedLocations2},
            {PSBusyPublicDX11Gfx9, expectedLocations3},
            {CSBusyPublicDX11Gfx9, expectedLocations4},
        };

        VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx9, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}

// regression test for GPA-123
TEST(CounterDLLTests, DX11Gfx8HSBusyHSTimeGSTime)
{
    #pragma region Gfx8
    {
        std::vector<unsigned int> counters =
        {
            HSBusyPublicDX11Gfx8,
            HSTimePublicDX11Gfx8,
            GSTimePublicDX11Gfx8
        };

        std::vector<uint32_t> expectedCountersPass0 =
        {
            13093, 13290, 13487, 13684, 13099, 13296, 13493, 13690, 10620, 13072,
            13269, 13466, 13663, 13075, 13272, 13469, 13666
        };

        std::vector<uint32_t> expectedCountersPass1 =
        {
            51132
        };

        std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsHSBusy
        {
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 7)
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsHSTime
        {
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 7)
            MakeExpectedCounterLocationEntry(1, 0)
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsGSTime
        {
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 9)
            MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 10)
            MakeExpectedCounterLocationEntry(0, 14)
            MakeExpectedCounterLocationEntry(0, 11)
            MakeExpectedCounterLocationEntry(0, 15)
            MakeExpectedCounterLocationEntry(0, 12)
            MakeExpectedCounterLocationEntry(0, 16)
            MakeExpectedCounterLocationEntry(1, 0)
        };

        std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
        {
            {HSBusyPublicDX11Gfx8, expectedLocationsHSBusy},
            {HSTimePublicDX11Gfx8, expectedLocationsHSTime},
            {GSTimePublicDX11Gfx8, expectedLocationsGSTime}
        };

        VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}

// regression test related to GPA-123
TEST(CounterDLLTests, DX11Gfx9HSTimeGSTime)
{
    #pragma region Gfx9
    {
        std::vector<unsigned int> counters =
        {
            HSTimePublicDX11Gfx9,
            GSTimePublicDX11Gfx9,
        };


        // Pass: 0  Counters: 17
        std::vector<uint32_t> expectedCountersPass0 =
        {
            16633, 16829, 17025, 17221, 16639, 16835, 17031, 17227, 23, 16621,
            16817, 17013, 17209, 16624, 16820, 17016, 17212
        };

        // Pass: 1  Counters: 1
        std::vector<uint32_t> expectedCountersPass1 =
        {
            55102
        };

        std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
        };


        // Result locations (Pass, Offset)

        // Pass: 0  Counters: 10
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
        {
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 7)
            MakeExpectedCounterLocationEntry(1, 0)
        };

        // Pass: 1  Counters: 13
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
        {
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 9)
            MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 10)
            MakeExpectedCounterLocationEntry(0, 14)
            MakeExpectedCounterLocationEntry(0, 11)
            MakeExpectedCounterLocationEntry(0, 15)
            MakeExpectedCounterLocationEntry(0, 12)
            MakeExpectedCounterLocationEntry(0, 16)
            MakeExpectedCounterLocationEntry(1, 0)
        };

        std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
        {
            {HSTimePublicDX11Gfx9, expectedLocations0},
            {GSTimePublicDX11Gfx9, expectedLocations1}
        };

        VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx9, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}

TEST(CounterDLLTests, DX11Gfx8VSBusy)
{
    #pragma region Gfx8
    {
        std::vector<unsigned int> counters = {VSBusyPublicDX11Gfx8};

        std::vector<uint32_t> expectedCountersPass0 =
        {
            13056, 13253, 13450, 13647, 13081, 13278, 13475, 13672, 13103, 13300,
            13497, 13694, 13125, 13322, 13519, 13716, 13065, 13262, 13459, 13656,
            13087, 13284, 13481, 13678, 10620
        };

        std::vector<uint32_t> expectedCountersPass1 =
        {
            13109, 13306, 13503, 13700
        };

        std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
            expectedCountersPass1,
        };

        std::map<uint32_t, GPA_CounterResultLocation> expectedLocationsVSBusy
        {
            MakeExpectedCounterLocationEntry(0, 24)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 16)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 20)
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(1, 0)
            MakeExpectedCounterLocationEntry(0, 12)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 17)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 21)
            MakeExpectedCounterLocationEntry(0, 9)
            MakeExpectedCounterLocationEntry(1, 1)
            MakeExpectedCounterLocationEntry(0, 13)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 18)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 22)
            MakeExpectedCounterLocationEntry(0, 10)
            MakeExpectedCounterLocationEntry(1, 2)
            MakeExpectedCounterLocationEntry(0, 14)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 19)
            MakeExpectedCounterLocationEntry(0, 7)
            MakeExpectedCounterLocationEntry(0, 23)
            MakeExpectedCounterLocationEntry(0, 11)
            MakeExpectedCounterLocationEntry(1, 3)
            MakeExpectedCounterLocationEntry(0, 15)
        };

        std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;
        expectedResultLocations[VSBusyPublicDX11Gfx8] = expectedLocationsVSBusy;

        VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}

TEST(CounterDLLTests, DX11Gfx9VSBusy)
{
    #pragma region Gfx9
    {
        std::vector<unsigned int> counters = {VSBusyPublicDX11Gfx9};

        // Pass: 0  Counters: 9
        std::vector<uint32_t> expectedCountersPass0 =
        {
            16602, 16798, 16994, 17190, 16611, 16807, 17003, 17199, 23
        };

        std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
        {
            expectedCountersPass0,
        };


        // Result locations (Pass, Offset)

        // Pass: 0  Counters: 5
        std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
        {
            MakeExpectedCounterLocationEntry(0, 8)
            MakeExpectedCounterLocationEntry(0, 0)
            MakeExpectedCounterLocationEntry(0, 4)
            MakeExpectedCounterLocationEntry(0, 1)
            MakeExpectedCounterLocationEntry(0, 5)
            MakeExpectedCounterLocationEntry(0, 2)
            MakeExpectedCounterLocationEntry(0, 6)
            MakeExpectedCounterLocationEntry(0, 3)
            MakeExpectedCounterLocationEntry(0, 7)
        };

        std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
        {
            { VSBusyPublicDX11Gfx9, expectedLocations0 }
        };

        VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx9, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
    }
    #pragma endregion
}

void TestGPUTimeVSBusyVSTimeCountersForDevice(unsigned int deviceId)
{
    // checks that different combinations of GPUTime / VSBusy / VSTime are scheduled correctly regardless of order of inclusion
    static uint32_t GPUTimeIndex;
    static uint32_t VSBusyIndex;
    static uint32_t VSTimeIndex;
    uint32_t        expectedPasses = 0;

    if (gDevIdVI == deviceId)
    {
        GPUTimeIndex   = GPUTimePublicDX11Gfx8;
        VSBusyIndex    = VSBusyPublicDX11Gfx8;
        VSTimeIndex    = VSTimePublicDX11Gfx8;
        expectedPasses = 3;
    }
    else if (gDevIdGfx9 == deviceId)
    {
        GPUTimeIndex   = GPUTimePublicDX11Gfx9;
        VSBusyIndex    = VSBusyPublicDX11Gfx9;
        VSTimeIndex    = VSTimePublicDX11Gfx9;
        expectedPasses = 2;
    }

    // counters to enable (GPUTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {GPUTimeIndex, VSBusyIndex}, expectedPasses);

    // counters to enable (VSBusy, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSBusyIndex, GPUTimeIndex}, expectedPasses);

    // counters to enable (VSBusy, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSBusyIndex, VSTimeIndex}, expectedPasses);

    // counters to enable (VSTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSTimeIndex, VSBusyIndex}, expectedPasses);

    // counters to enable (GPUTime, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {GPUTimeIndex, VSTimeIndex}, expectedPasses);

    // counters to enable (VSTime, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSTimeIndex, GPUTimeIndex}, expectedPasses);

    // counters to enable (GPUTime, VSBusy, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {GPUTimeIndex, VSBusyIndex, VSTimeIndex}, expectedPasses);

    // counters to enable (GPUTime, VSTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {GPUTimeIndex, VSTimeIndex, VSBusyIndex}, expectedPasses);

    // counters to enable (VSTime, GPUTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSTimeIndex, GPUTimeIndex, VSBusyIndex}, expectedPasses);

    // counters to enable (VSTime, VSBusy, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSTimeIndex, VSBusyIndex, GPUTimeIndex}, expectedPasses);

    // counters to enable (VSBusy, GPUTime, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSBusyIndex, GPUTimeIndex, VSTimeIndex}, expectedPasses);

    // counters to enable (VSBusy, VSTime, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> {VSBusyIndex, VSTimeIndex, GPUTimeIndex}, expectedPasses);
}

TEST(CounterDLLTests, DX11VIGPUTimeVSBusyVSTimeCounters)
{
    TestGPUTimeVSBusyVSTimeCountersForDevice(gDevIdVI);
}

TEST(CounterDLLTests, DX11Gfx9GPUTimeVSBusyVSTimeCounters)
{
    TestGPUTimeVSBusyVSTimeCountersForDevice(gDevIdGfx9);
}

void TestD3D11QueryCounter(unsigned int deviceId,
                           unsigned int D3DQueryCounterIndex,
                           unsigned int publicCounterCount,
                           unsigned int hardwareCounterCount,
                           unsigned int gpuTimeHWCounterIndex = 0)
{
    std::vector<unsigned int> counters;

    static const int GPUTimePublicCounterIndex = 0;  // public GPUTime counter is always index 0

    if (gpuTimeHWCounterIndex != 0)
    {
        counters.push_back(GPUTimePublicCounterIndex);
    }

    // the D3D query counters appear after the public counters
    unsigned int queryCounterIndex = publicCounterCount + D3DQueryCounterIndex;

#ifdef AMDT_INTERNAL
    // in the internal build, the D3D query counters are also after the hardware counters
    queryCounterIndex += hardwareCounterCount;
#endif

    counters.push_back(queryCounterIndex);

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsGPUTime;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsD3DQuery;

    std::vector<unsigned int> expectedCountersPass1;
    std::vector<unsigned int> expectedCountersPass2;

    if (gpuTimeHWCounterIndex != 0)
    {
        // GPUTime
        expectedCountersPass1.push_back(gpuTimeHWCounterIndex);  // the internal counter
        expectedLocationsGPUTime[gpuTimeHWCounterIndex] = MakeLocation(0, 0);

        // D3DQuery
        expectedCountersPass2.push_back(hardwareCounterCount + D3DQueryCounterIndex);
        expectedLocationsD3DQuery[hardwareCounterCount + D3DQueryCounterIndex] = MakeLocation(1, 0);
    }
    else
    {
        // D3DQuery
        expectedCountersPass1.push_back(hardwareCounterCount + D3DQueryCounterIndex);
        expectedLocationsD3DQuery[hardwareCounterCount + D3DQueryCounterIndex] = MakeLocation(0, 0);
    }

    std::vector<std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);

    if (!expectedCountersPass2.empty())
    {
        expectedHwCountersPerPass.push_back(expectedCountersPass2);
    }

    std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;

    if (gpuTimeHWCounterIndex != 0)
    {
        // GPUTime
        expectedResultLocations[GPUTimePublicCounterIndex] = expectedLocationsGPUTime;
    }

    expectedResultLocations[queryCounterIndex] = expectedLocationsD3DQuery;

    VerifyCountersInPass(GPA_API_DIRECTX_11, deviceId, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

TEST(CounterDLLTests, DX11VIPSBusyCounterResult)
{
    // test the result of PSBusy, which uses 9 internal counters
    unsigned int requiredCount = 9;

    // fabricate some results that will allow us to confirm the PSBusy counter
    // each result is 64 bit, so 8 chars.
    gpa_uint64* pAllResults = new(std::nothrow) gpa_uint64[requiredCount * 8];
    ASSERT_TRUE(nullptr != pAllResults);
    memset(pAllResults, 0, requiredCount * 8);

    pAllResults[0 * 8] = 1;
    pAllResults[1 * 8] = 1;
    pAllResults[2 * 8] = 1;
    pAllResults[3 * 8] = 1;
    pAllResults[4 * 8] = 1;
    pAllResults[5 * 8] = 1;
    pAllResults[6 * 8] = 1;
    pAllResults[7 * 8] = 1;
    pAllResults[8 * 8] = 2;  // GUI_ACTIVE

    // copy results into the vector
    std::vector<const gpa_uint64*> sampleResults;

    for (unsigned int i = 0; i < requiredCount; i++)
    {
        sampleResults.push_back(&(pAllResults[i * 8]));
    }

    VerifyCounterCalculation(GPA_API_DIRECTX_11, gDevIdVI, FALSE, "PSBusy", sampleResults, 50);

    delete[] pAllResults;
}

TEST(CounterDLLTests, DX11EnableAndDisable)
{
    GPA_API_Type api      = GPA_API_DIRECTX_11;
    unsigned int deviceId = gDevIdVI;

    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE) nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc) nullptr, GPA_GetAvailableCounters_fn);

    IGPACounterAccessor*  pCounterAccessor  = nullptr;
    IGPACounterScheduler* pCounterScheduler = nullptr;
    GPA_Status            status =
        GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, FALSE, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
    ASSERT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);

    // enable a counter
    GPA_Status enabled = pCounterScheduler->EnableCounter(0);
    EXPECT_EQ(GPA_STATUS_OK, enabled);

    gpa_uint32 requiredPasses  = 0;
    GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(1, requiredPasses);

    // enable another counter
    enabled = pCounterScheduler->EnableCounter(1);
    EXPECT_EQ(GPA_STATUS_OK, enabled);

    passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(2, requiredPasses);

    // disable the counters
    pCounterScheduler->DisableAllCounters();

    passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(0, requiredPasses);

    // enable the second counter again
    enabled = pCounterScheduler->EnableCounter(1);
    EXPECT_EQ(GPA_STATUS_OK, enabled);

    passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(1, requiredPasses);
}

#endif

/// GPA-127 Validation test.
/// SQ counters must be isolated from TCC/TA/TCP/TCA/TD counters because PAL is now setting the
/// SQ_PERF_CTRL register field to enable all shader waves when counters from the texture blocks are used.

#ifdef _WIN32

TEST(CounterDLLTests, SqIsolatedCounterSplitScheduler)
{
    // CSVFetchInstsDX11Gfx8 TA and SQ counters
    std::vector<uint32_t> counters = {CSVFetchInstsPublicDX11Gfx8};

    // Pass: 0  Counters: 64
    std::vector<uint32_t> expectedCountersPass0 =
    {
        23512, 23631, 23750, 23869, 23988, 24107, 24226, 24345, 24464, 24583,
        24702, 24821, 24940, 25059, 25178, 25297, 25416, 25535, 25654, 25773,
        25892, 26011, 26130, 26249, 26368, 26487, 26606, 26725, 26844, 26963,
        27082, 27201, 27320, 27439, 27558, 27677, 27796, 27915, 28034, 28153,
        28272, 28391, 28510, 28629, 28748, 28867, 28986, 29105, 29224, 29343,
        29462, 29581, 29700, 29819, 29938, 30057, 30176, 30295, 30414, 30533,
        30652, 30771, 30890, 31009
    };

    // Pass: 1  Counters: 16
    std::vector<uint32_t> expectedCountersPass1 =
    {
        22243, 22542, 22841, 23140, 22219, 22518, 22817, 23116, 13114, 13311,
        13508, 13705, 13120, 13317, 13514, 13711
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
    };


    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 74
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 24)
        MakeExpectedCounterLocationEntry(0, 25)
        MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 27)
        MakeExpectedCounterLocationEntry(0, 28)
        MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 30)
        MakeExpectedCounterLocationEntry(0, 31)
        MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 36)
        MakeExpectedCounterLocationEntry(0, 37)
        MakeExpectedCounterLocationEntry(0, 38)
        MakeExpectedCounterLocationEntry(0, 39)
        MakeExpectedCounterLocationEntry(0, 40)
        MakeExpectedCounterLocationEntry(0, 41)
        MakeExpectedCounterLocationEntry(0, 42)
        MakeExpectedCounterLocationEntry(0, 43)
        MakeExpectedCounterLocationEntry(0, 44)
        MakeExpectedCounterLocationEntry(0, 45)
        MakeExpectedCounterLocationEntry(0, 46)
        MakeExpectedCounterLocationEntry(0, 47)
        MakeExpectedCounterLocationEntry(0, 48)
        MakeExpectedCounterLocationEntry(0, 49)
        MakeExpectedCounterLocationEntry(0, 50)
        MakeExpectedCounterLocationEntry(0, 51)
        MakeExpectedCounterLocationEntry(0, 52)
        MakeExpectedCounterLocationEntry(0, 53)
        MakeExpectedCounterLocationEntry(0, 54)
        MakeExpectedCounterLocationEntry(0, 55)
        MakeExpectedCounterLocationEntry(0, 56)
        MakeExpectedCounterLocationEntry(0, 57)
        MakeExpectedCounterLocationEntry(0, 58)
        MakeExpectedCounterLocationEntry(0, 59)
        MakeExpectedCounterLocationEntry(0, 60)
        MakeExpectedCounterLocationEntry(0, 61)
        MakeExpectedCounterLocationEntry(0, 62)
        MakeExpectedCounterLocationEntry(0, 63)
    };

    std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations = {{CSVFetchInstsPublicDX11Gfx8, expectedLocations0}};

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

/// GPA-159 Validation Test
/// Select the "HSBusyCycles", "HSTime (ns)", "PSBusyCycles", "PSTime (ns)" counters together

TEST(CounterDLLTests, Gpa159MultipleTimingCounters)
{
    std::vector<uint32_t> counters =
    {
        HSBusyCyclesPublicDX12Gfx8,
        HSTimePublicDX12Gfx8,
        PSBusyCyclesPublicDX12Gfx8,
        PSTimePublicDX12Gfx8,
    };

    // Pass: 0  Counters: 17
    std::vector<uint32_t> expectedCountersPass0 = {2893, 3090, 3287, 3484, 2899, 3096, 3293, 3490, 49743, 2925, 3122, 3319, 3516, 2930, 3127, 3324, 3521};

    // Pass: 1  Counters: 1
    std::vector<uint32_t> expectedCountersPass1 = {51131};

    std::vector<std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
    };

    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 9
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 7)
    };

    // Pass: 1  Counters: 10
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
    {
        MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(
            0, 5) MakeExpectedCounterLocationEntry(0, 2) MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8) MakeExpectedCounterLocationEntry(1, 0)};

    // Pass: 2  Counters: 18
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
    {
        MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 14) MakeExpectedCounterLocationEntry(0, 11) MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 16)};

    // Pass: 3  Counters: 19
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations3
    {
        MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(
            0, 14) MakeExpectedCounterLocationEntry(0, 11) MakeExpectedCounterLocationEntry(0, 15) MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 8) MakeExpectedCounterLocationEntry(1, 0)};

    std::map<uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations = {{HSBusyCyclesPublicDX12Gfx8, expectedLocations0},
        {HSTimePublicDX12Gfx8, expectedLocations1},
        {PSBusyCyclesPublicDX12Gfx8, expectedLocations2},
        {PSTimePublicDX12Gfx8, expectedLocations3}
    };

    VerifyCountersInPass(GPA_API_DIRECTX_12, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

/// GPA-85 Validation Test
/// Enable the following counters in this order:
/// VSVerticesIn
/// VSVALUInstCount
/// VSVALUBusy
/// VSSALUInstCount
/// VSSALUBusy
/// CSBusy
/// CSTime
/// DSBusy
/// DSTime
/// DepthStencilTestBusy
/// GPUBusy
/// GPUTime
/// GSBusy
/// GSTime
/// PSBusy
/// PSTime
/// PrimitiveAssemblyBusy
/// TessallatorBusy
/// TexUnitBusy
/// HSTime
/// HSBusy
/// VSBusy
/// VSTime

TEST(CounterDLLTests, Gpa85MultipleTimingCounters)
{
    std::vector<uint32_t> counters =
    {
        VSVerticesInPublicDX12Gfx8,
        VSVALUInstCountPublicDX12Gfx8,
        VSVALUBusyPublicDX12Gfx8,
        VSSALUInstCountPublicDX12Gfx8,
        VSSALUBusyPublicDX12Gfx8,
        CSBusyPublicDX12Gfx8,
        CSTimePublicDX12Gfx8,
        DSBusyPublicDX12Gfx8,
        DSTimePublicDX12Gfx8,
        DepthStencilTestBusyPublicDX12Gfx8,
        GPUBusyPublicDX12Gfx8,
        GPUTimePublicDX12Gfx8,
        GSBusyPublicDX12Gfx8,
        GSTimePublicDX12Gfx8,
        PSBusyPublicDX12Gfx8,
        PSTimePublicDX12Gfx8,
        PrimitiveAssemblyBusyPublicDX12Gfx8,
        TessellatorBusyPublicDX12Gfx8,
        TexUnitBusyPublicDX12Gfx8,
        HSTimePublicDX12Gfx8,
        HSBusyPublicDX12Gfx8,
        VSBusyPublicDX12Gfx8,
        VSTimePublicDX12Gfx8,
    };

    // Pass: 0  Counters: 118
    std::vector<uint32_t> expectedCountersPass0 =
    {
        13362, 13481, 13600, 13719, 13838, 13957, 14076, 14195, 14314, 14433, 14552, 14671, 14790, 14909, 15028, 15147, 15266, 15385, 15504, 15623,
        15742, 15861, 15980, 16099, 16218, 16337, 16456, 16575, 16694, 16813, 16932, 17051, 17170, 17289, 17408, 17527, 17646, 17765, 17884, 18003,
        18122, 18241, 18360, 18479, 18598, 18717, 18836, 18955, 19074, 19193, 19312, 19431, 19550, 19669, 19788, 19907, 20026, 20145, 20264, 20383,
        20502, 20621, 20740, 20859, 49743, 2856,  3053,  3250,  3447,  2881,  3078,  3275,  3472,  2903,  3100,  3297,  3494,  2925,  3122,  3319,
        3516,  2865,  3062,  3259,  3456,  2887,  3084,  3281,  3478,  39289, 39546, 39803, 40060, 40317, 40574, 40831, 41088, 41345, 41602, 41859,
        42116, 42373, 42630, 42887, 43144, 87,    234,   381,   528,   68,    215,   362,   509,   163,   310,   457,   604,   49741
    };

    // Pass: 1  Counters: 69
    std::vector<uint32_t> expectedCountersPass1 = {2856, 3053, 3250,  3447, 2881, 3078, 3275, 3472, 2925, 3122, 3319, 3516, 2887, 3084, 3281, 3478, 2909, 3106,
                                                   3303, 3500, 49743, 760,  913,  1066, 1219, 764,  917,  1070, 1223, 716,  869,  1022, 1175, 728,  881,  1034,
                                                   1187, 4865, 5164,  5463, 5762, 4843, 5142, 5441, 5740, 4853, 5152, 5451, 5750, 4869, 5168, 5467, 5766, 2930,
                                                   3127, 3324, 3521,  4920, 5219, 5518, 5817, 4925, 5224, 5523, 5822, 191,  338,  485,  632
                                                  };

    // Pass: 2  Counters: 57
    std::vector<uint32_t> expectedCountersPass2 = {2913, 3110,  3307,  3504,  2917,  3114,  3311, 3508, 2919,  3116,  3313, 3510, 2923,  3120,  3317,
                                                   3514, 49743, 9649,  9948,  10247, 10546, 9627, 9926, 10225, 10524, 9637, 9936, 10235, 10534, 9653,
                                                   9952, 10251, 10550, 2872,  3069,  3266,  3463, 2875, 3072,  3269,  3466, 9704, 10003, 10302, 10601,
                                                   9709, 10008, 10307, 10606, 717,   870,   1023, 1176, 729,   882,   1035, 1188
                                                  };

    // Pass: 3  Counters: 29
    std::vector<uint32_t> expectedCountersPass3 = {2893, 3090, 3287, 3484, 2899, 3096, 3293, 3490, 49743, 7257, 7556, 7855, 8154, 7235, 7534,
                                                   7833, 8132, 7261, 7560, 7859, 8158, 7312, 7611, 7910,  8209, 7317, 7616, 7915, 8214
                                                  };

    // Pass: 4  Counters: 1
    std::vector<uint32_t> expectedCountersPass4 = {51131};

    std::vector<std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
        expectedCountersPass2,
        expectedCountersPass3,
        expectedCountersPass4,
    };

    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 23
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 109) MakeExpectedCounterLocationEntry(0, 105) MakeExpectedCounterLocationEntry(0, 113)
        MakeExpectedCounterLocationEntry(0, 110) MakeExpectedCounterLocationEntry(0, 106) MakeExpectedCounterLocationEntry(0, 114)
        MakeExpectedCounterLocationEntry(0, 111) MakeExpectedCounterLocationEntry(0, 107) MakeExpectedCounterLocationEntry(0, 115)
        MakeExpectedCounterLocationEntry(0, 112) MakeExpectedCounterLocationEntry(0, 108) MakeExpectedCounterLocationEntry(0, 116)};

    // Pass: 1  Counters: 24
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
    {
        MakeExpectedCounterLocationEntry(1, 41) MakeExpectedCounterLocationEntry(1, 45) MakeExpectedCounterLocationEntry(
            1, 37) MakeExpectedCounterLocationEntry(1, 42) MakeExpectedCounterLocationEntry(1, 46) MakeExpectedCounterLocationEntry(1, 38)
        MakeExpectedCounterLocationEntry(1, 43) MakeExpectedCounterLocationEntry(1, 47) MakeExpectedCounterLocationEntry(1, 39)
        MakeExpectedCounterLocationEntry(1, 44) MakeExpectedCounterLocationEntry(1, 48) MakeExpectedCounterLocationEntry(1, 40)
        MakeExpectedCounterLocationEntry(3, 13) MakeExpectedCounterLocationEntry(3, 9) MakeExpectedCounterLocationEntry(3, 14)
        MakeExpectedCounterLocationEntry(3, 10) MakeExpectedCounterLocationEntry(3, 15) MakeExpectedCounterLocationEntry(3, 11)
        MakeExpectedCounterLocationEntry(3, 16) MakeExpectedCounterLocationEntry(3, 12) MakeExpectedCounterLocationEntry(2, 21)
        MakeExpectedCounterLocationEntry(2, 25) MakeExpectedCounterLocationEntry(2, 17) MakeExpectedCounterLocationEntry(2, 22)
        MakeExpectedCounterLocationEntry(2, 26) MakeExpectedCounterLocationEntry(2, 18) MakeExpectedCounterLocationEntry(2, 23)
        MakeExpectedCounterLocationEntry(2, 27) MakeExpectedCounterLocationEntry(2, 19) MakeExpectedCounterLocationEntry(2, 24)
        MakeExpectedCounterLocationEntry(2, 28) MakeExpectedCounterLocationEntry(2, 20)};

    // Pass: 2  Counters: 26
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
    {
        MakeExpectedCounterLocationEntry(1, 45) MakeExpectedCounterLocationEntry(1, 57) MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(1, 58) MakeExpectedCounterLocationEntry(1, 47) MakeExpectedCounterLocationEntry(1, 59)
        MakeExpectedCounterLocationEntry(1, 48) MakeExpectedCounterLocationEntry(1, 60) MakeExpectedCounterLocationEntry(3, 21)
        MakeExpectedCounterLocationEntry(3, 22) MakeExpectedCounterLocationEntry(3, 23) MakeExpectedCounterLocationEntry(3, 24)
        MakeExpectedCounterLocationEntry(2, 25) MakeExpectedCounterLocationEntry(2, 41) MakeExpectedCounterLocationEntry(2, 26)
        MakeExpectedCounterLocationEntry(2, 42) MakeExpectedCounterLocationEntry(2, 27) MakeExpectedCounterLocationEntry(2, 43)
        MakeExpectedCounterLocationEntry(2, 28) MakeExpectedCounterLocationEntry(2, 44) MakeExpectedCounterLocationEntry(3, 8)};

    // Pass: 3  Counters: 25
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations3
    {
        MakeExpectedCounterLocationEntry(1, 41) MakeExpectedCounterLocationEntry(1, 45) MakeExpectedCounterLocationEntry(
            1, 49) MakeExpectedCounterLocationEntry(1, 42) MakeExpectedCounterLocationEntry(1, 46) MakeExpectedCounterLocationEntry(1, 50)
        MakeExpectedCounterLocationEntry(1, 43) MakeExpectedCounterLocationEntry(1, 47) MakeExpectedCounterLocationEntry(1, 51)
        MakeExpectedCounterLocationEntry(1, 44) MakeExpectedCounterLocationEntry(1, 48) MakeExpectedCounterLocationEntry(1, 52)
        MakeExpectedCounterLocationEntry(3, 13) MakeExpectedCounterLocationEntry(3, 17) MakeExpectedCounterLocationEntry(3, 14)
        MakeExpectedCounterLocationEntry(3, 18) MakeExpectedCounterLocationEntry(3, 15) MakeExpectedCounterLocationEntry(3, 19)
        MakeExpectedCounterLocationEntry(3, 16) MakeExpectedCounterLocationEntry(3, 20) MakeExpectedCounterLocationEntry(2, 21)
        MakeExpectedCounterLocationEntry(2, 25) MakeExpectedCounterLocationEntry(2, 29) MakeExpectedCounterLocationEntry(2, 22)
        MakeExpectedCounterLocationEntry(2, 26) MakeExpectedCounterLocationEntry(2, 30) MakeExpectedCounterLocationEntry(2, 23)
        MakeExpectedCounterLocationEntry(2, 27) MakeExpectedCounterLocationEntry(2, 31) MakeExpectedCounterLocationEntry(2, 24)
        MakeExpectedCounterLocationEntry(2, 28) MakeExpectedCounterLocationEntry(2, 32)};

    // Pass: 4  Counters: 28
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations4
    {
        MakeExpectedCounterLocationEntry(1, 45) MakeExpectedCounterLocationEntry(1, 61) MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(1, 62) MakeExpectedCounterLocationEntry(1, 47) MakeExpectedCounterLocationEntry(1, 63)
        MakeExpectedCounterLocationEntry(1, 48) MakeExpectedCounterLocationEntry(1, 64) MakeExpectedCounterLocationEntry(3, 25)
        MakeExpectedCounterLocationEntry(3, 26) MakeExpectedCounterLocationEntry(3, 27) MakeExpectedCounterLocationEntry(3, 28)
        MakeExpectedCounterLocationEntry(2, 25) MakeExpectedCounterLocationEntry(2, 45) MakeExpectedCounterLocationEntry(2, 26)
        MakeExpectedCounterLocationEntry(2, 46) MakeExpectedCounterLocationEntry(2, 27) MakeExpectedCounterLocationEntry(2, 47)
        MakeExpectedCounterLocationEntry(2, 28) MakeExpectedCounterLocationEntry(2, 48) MakeExpectedCounterLocationEntry(3, 8)};

    // Pass: 5  Counters: 20
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations5
    {
        MakeExpectedCounterLocationEntry(2, 0) MakeExpectedCounterLocationEntry(2, 4) MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 12) MakeExpectedCounterLocationEntry(2, 1) MakeExpectedCounterLocationEntry(2, 5)
        MakeExpectedCounterLocationEntry(2, 9) MakeExpectedCounterLocationEntry(2, 13) MakeExpectedCounterLocationEntry(2, 2)
        MakeExpectedCounterLocationEntry(2, 6) MakeExpectedCounterLocationEntry(2, 10) MakeExpectedCounterLocationEntry(2, 14)
        MakeExpectedCounterLocationEntry(2, 3) MakeExpectedCounterLocationEntry(2, 7) MakeExpectedCounterLocationEntry(2, 11)
        MakeExpectedCounterLocationEntry(2, 15) MakeExpectedCounterLocationEntry(2, 16)};

    // Pass: 6  Counters: 22
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations6
    {
        MakeExpectedCounterLocationEntry(2, 0) MakeExpectedCounterLocationEntry(2, 4) MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 12) MakeExpectedCounterLocationEntry(2, 1) MakeExpectedCounterLocationEntry(2, 5)
        MakeExpectedCounterLocationEntry(2, 9) MakeExpectedCounterLocationEntry(2, 13) MakeExpectedCounterLocationEntry(2, 2)
        MakeExpectedCounterLocationEntry(2, 6) MakeExpectedCounterLocationEntry(2, 10) MakeExpectedCounterLocationEntry(2, 14)
        MakeExpectedCounterLocationEntry(2, 3) MakeExpectedCounterLocationEntry(2, 7) MakeExpectedCounterLocationEntry(2, 11)
        MakeExpectedCounterLocationEntry(2, 15) MakeExpectedCounterLocationEntry(2, 16) MakeExpectedCounterLocationEntry(4, 0)};

    // Pass: 7  Counters: 11
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations7
    {
        MakeExpectedCounterLocationEntry(1, 0) MakeExpectedCounterLocationEntry(1, 4) MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(1, 16) MakeExpectedCounterLocationEntry(1, 8) MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 5) MakeExpectedCounterLocationEntry(1, 13) MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 2) MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 14) MakeExpectedCounterLocationEntry(1, 18) MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 3) MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(1, 19) MakeExpectedCounterLocationEntry(1, 11) MakeExpectedCounterLocationEntry(1, 20)};

    // Pass: 8  Counters: 13
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations8
    {
        MakeExpectedCounterLocationEntry(1, 0) MakeExpectedCounterLocationEntry(1, 4) MakeExpectedCounterLocationEntry(1, 12) MakeExpectedCounterLocationEntry(
            1, 16) MakeExpectedCounterLocationEntry(1, 8) MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(1, 13) MakeExpectedCounterLocationEntry(1, 17) MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 2) MakeExpectedCounterLocationEntry(1, 6) MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(1, 18) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 15) MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(1, 11) MakeExpectedCounterLocationEntry(1, 20) MakeExpectedCounterLocationEntry(4, 0)};

    // Pass: 9  Counters: 103
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations9
    {
        MakeExpectedCounterLocationEntry(0, 89) MakeExpectedCounterLocationEntry(0, 90) MakeExpectedCounterLocationEntry(0, 91)
        MakeExpectedCounterLocationEntry(0, 92) MakeExpectedCounterLocationEntry(0, 93) MakeExpectedCounterLocationEntry(0, 94)
        MakeExpectedCounterLocationEntry(0, 95) MakeExpectedCounterLocationEntry(0, 96) MakeExpectedCounterLocationEntry(0, 97)
        MakeExpectedCounterLocationEntry(0, 98) MakeExpectedCounterLocationEntry(0, 99) MakeExpectedCounterLocationEntry(0, 100)
        MakeExpectedCounterLocationEntry(0, 101) MakeExpectedCounterLocationEntry(0, 102) MakeExpectedCounterLocationEntry(0, 103)
        MakeExpectedCounterLocationEntry(0, 104) MakeExpectedCounterLocationEntry(0, 64)};

    // Pass: 10  Counters: 1
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations10{MakeExpectedCounterLocationEntry(0, 117) MakeExpectedCounterLocationEntry(0, 64)};

    // Pass: 11  Counters: 0
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations11{MakeExpectedCounterLocationEntry(4, 0)};

    // Pass: 12  Counters: 14
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations12
    {
        MakeExpectedCounterLocationEntry(2, 33) MakeExpectedCounterLocationEntry(2, 37) MakeExpectedCounterLocationEntry(2, 34)
        MakeExpectedCounterLocationEntry(2, 38) MakeExpectedCounterLocationEntry(2, 35) MakeExpectedCounterLocationEntry(2, 39)
        MakeExpectedCounterLocationEntry(2, 36) MakeExpectedCounterLocationEntry(2, 40) MakeExpectedCounterLocationEntry(2, 16)};

    // Pass: 13  Counters: 16
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations13
    {
        MakeExpectedCounterLocationEntry(2, 33) MakeExpectedCounterLocationEntry(2, 37) MakeExpectedCounterLocationEntry(2, 34)
        MakeExpectedCounterLocationEntry(2, 38) MakeExpectedCounterLocationEntry(2, 35) MakeExpectedCounterLocationEntry(2, 39)
        MakeExpectedCounterLocationEntry(2, 36) MakeExpectedCounterLocationEntry(2, 40) MakeExpectedCounterLocationEntry(2, 16)
        MakeExpectedCounterLocationEntry(4, 0)};

    // Pass: 14  Counters: 17
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations14
    {
        MakeExpectedCounterLocationEntry(1, 8) MakeExpectedCounterLocationEntry(1, 53) MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 54) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 55)
        MakeExpectedCounterLocationEntry(1, 11) MakeExpectedCounterLocationEntry(1, 56) MakeExpectedCounterLocationEntry(1, 20)};

    // Pass: 15  Counters: 19
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations15
    {
        MakeExpectedCounterLocationEntry(1, 8) MakeExpectedCounterLocationEntry(1, 53) MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(
            1, 54) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 55) MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 56) MakeExpectedCounterLocationEntry(1, 20) MakeExpectedCounterLocationEntry(4, 0)};

    // Pass: 16  Counters: 52
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations16
    {
        MakeExpectedCounterLocationEntry(1, 29) MakeExpectedCounterLocationEntry(2, 49) MakeExpectedCounterLocationEntry(1, 33)
        MakeExpectedCounterLocationEntry(2, 53) MakeExpectedCounterLocationEntry(1, 21) MakeExpectedCounterLocationEntry(1, 25)
        MakeExpectedCounterLocationEntry(1, 30) MakeExpectedCounterLocationEntry(2, 50) MakeExpectedCounterLocationEntry(1, 34)
        MakeExpectedCounterLocationEntry(2, 54) MakeExpectedCounterLocationEntry(1, 22) MakeExpectedCounterLocationEntry(1, 26)
        MakeExpectedCounterLocationEntry(1, 31) MakeExpectedCounterLocationEntry(2, 51) MakeExpectedCounterLocationEntry(1, 35)
        MakeExpectedCounterLocationEntry(2, 55) MakeExpectedCounterLocationEntry(1, 23) MakeExpectedCounterLocationEntry(1, 27)
        MakeExpectedCounterLocationEntry(1, 32) MakeExpectedCounterLocationEntry(2, 52) MakeExpectedCounterLocationEntry(1, 36)
        MakeExpectedCounterLocationEntry(2, 56) MakeExpectedCounterLocationEntry(1, 24) MakeExpectedCounterLocationEntry(1, 28)
        MakeExpectedCounterLocationEntry(1, 20)};

    // Pass: 17  Counters: 3
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations17{MakeExpectedCounterLocationEntry(1, 65) MakeExpectedCounterLocationEntry(
                                                                          1, 66) MakeExpectedCounterLocationEntry(1, 67) MakeExpectedCounterLocationEntry(1, 68) MakeExpectedCounterLocationEntry(1, 20)};

    // Pass: 18  Counters: 94
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations18
    {
        MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 15) MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 18) MakeExpectedCounterLocationEntry(0, 19) MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 21) MakeExpectedCounterLocationEntry(0, 22) MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 24) MakeExpectedCounterLocationEntry(0, 25) MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 27) MakeExpectedCounterLocationEntry(0, 28) MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 30) MakeExpectedCounterLocationEntry(0, 31) MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 33) MakeExpectedCounterLocationEntry(0, 34) MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 36) MakeExpectedCounterLocationEntry(0, 37) MakeExpectedCounterLocationEntry(0, 38)
        MakeExpectedCounterLocationEntry(0, 39) MakeExpectedCounterLocationEntry(0, 40) MakeExpectedCounterLocationEntry(0, 41)
        MakeExpectedCounterLocationEntry(0, 42) MakeExpectedCounterLocationEntry(0, 43) MakeExpectedCounterLocationEntry(0, 44)
        MakeExpectedCounterLocationEntry(0, 45) MakeExpectedCounterLocationEntry(0, 46) MakeExpectedCounterLocationEntry(0, 47)
        MakeExpectedCounterLocationEntry(0, 48) MakeExpectedCounterLocationEntry(0, 49) MakeExpectedCounterLocationEntry(0, 50)
        MakeExpectedCounterLocationEntry(0, 51) MakeExpectedCounterLocationEntry(0, 52) MakeExpectedCounterLocationEntry(0, 53)
        MakeExpectedCounterLocationEntry(0, 54) MakeExpectedCounterLocationEntry(0, 55) MakeExpectedCounterLocationEntry(0, 56)
        MakeExpectedCounterLocationEntry(0, 57) MakeExpectedCounterLocationEntry(0, 58) MakeExpectedCounterLocationEntry(0, 59)
        MakeExpectedCounterLocationEntry(0, 60) MakeExpectedCounterLocationEntry(0, 61) MakeExpectedCounterLocationEntry(0, 62)
        MakeExpectedCounterLocationEntry(0, 63) MakeExpectedCounterLocationEntry(0, 64)};

    // Pass: 19  Counters: 10
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations19
    {
        MakeExpectedCounterLocationEntry(3, 0) MakeExpectedCounterLocationEntry(3, 4) MakeExpectedCounterLocationEntry(3, 1)
        MakeExpectedCounterLocationEntry(3, 5) MakeExpectedCounterLocationEntry(3, 2) MakeExpectedCounterLocationEntry(3, 6)
        MakeExpectedCounterLocationEntry(3, 3) MakeExpectedCounterLocationEntry(3, 7) MakeExpectedCounterLocationEntry(3, 8)
        MakeExpectedCounterLocationEntry(4, 0)};

    // Pass: 20  Counters: 8
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations20
    {
        MakeExpectedCounterLocationEntry(3, 0) MakeExpectedCounterLocationEntry(3, 4) MakeExpectedCounterLocationEntry(3, 1)
        MakeExpectedCounterLocationEntry(3, 5) MakeExpectedCounterLocationEntry(3, 2) MakeExpectedCounterLocationEntry(3, 6)
        MakeExpectedCounterLocationEntry(3, 3) MakeExpectedCounterLocationEntry(3, 7) MakeExpectedCounterLocationEntry(3, 8)};

    // Pass: 21  Counters: 5
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations21
    {
        MakeExpectedCounterLocationEntry(0, 65) MakeExpectedCounterLocationEntry(0, 81) MakeExpectedCounterLocationEntry(0, 69)
        MakeExpectedCounterLocationEntry(0, 85) MakeExpectedCounterLocationEntry(0, 73) MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 77) MakeExpectedCounterLocationEntry(0, 66) MakeExpectedCounterLocationEntry(0, 82)
        MakeExpectedCounterLocationEntry(0, 70) MakeExpectedCounterLocationEntry(0, 86) MakeExpectedCounterLocationEntry(0, 74)
        MakeExpectedCounterLocationEntry(1, 17) MakeExpectedCounterLocationEntry(0, 78) MakeExpectedCounterLocationEntry(0, 67)
        MakeExpectedCounterLocationEntry(0, 83) MakeExpectedCounterLocationEntry(0, 71) MakeExpectedCounterLocationEntry(0, 87)
        MakeExpectedCounterLocationEntry(0, 75) MakeExpectedCounterLocationEntry(1, 18) MakeExpectedCounterLocationEntry(0, 79)
        MakeExpectedCounterLocationEntry(0, 68) MakeExpectedCounterLocationEntry(0, 84) MakeExpectedCounterLocationEntry(0, 72)
        MakeExpectedCounterLocationEntry(0, 88) MakeExpectedCounterLocationEntry(0, 76) MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 80) MakeExpectedCounterLocationEntry(0, 64)};

    // Pass: 22  Counters: 7
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations22
    {
        MakeExpectedCounterLocationEntry(0, 65) MakeExpectedCounterLocationEntry(0, 81) MakeExpectedCounterLocationEntry(
            0, 69) MakeExpectedCounterLocationEntry(0, 85) MakeExpectedCounterLocationEntry(0, 73) MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 77) MakeExpectedCounterLocationEntry(0, 66) MakeExpectedCounterLocationEntry(0, 82)
        MakeExpectedCounterLocationEntry(0, 70) MakeExpectedCounterLocationEntry(0, 86) MakeExpectedCounterLocationEntry(0, 74)
        MakeExpectedCounterLocationEntry(1, 17) MakeExpectedCounterLocationEntry(0, 78) MakeExpectedCounterLocationEntry(0, 67)
        MakeExpectedCounterLocationEntry(0, 83) MakeExpectedCounterLocationEntry(0, 71) MakeExpectedCounterLocationEntry(0, 87)
        MakeExpectedCounterLocationEntry(0, 75) MakeExpectedCounterLocationEntry(1, 18) MakeExpectedCounterLocationEntry(0, 79)
        MakeExpectedCounterLocationEntry(0, 68) MakeExpectedCounterLocationEntry(0, 84) MakeExpectedCounterLocationEntry(0, 72)
        MakeExpectedCounterLocationEntry(0, 88) MakeExpectedCounterLocationEntry(0, 76) MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 80) MakeExpectedCounterLocationEntry(0, 64) MakeExpectedCounterLocationEntry(4, 0)};

    std::map<uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
    {
        {VSVerticesInPublicDX12Gfx8, expectedLocations0},
        {VSVALUInstCountPublicDX12Gfx8, expectedLocations1},
        {VSVALUBusyPublicDX12Gfx8, expectedLocations2},
        {VSSALUInstCountPublicDX12Gfx8, expectedLocations3},
        {VSSALUBusyPublicDX12Gfx8, expectedLocations4},
        {CSBusyPublicDX12Gfx8, expectedLocations5},
        {CSTimePublicDX12Gfx8, expectedLocations6},
        {DSBusyPublicDX12Gfx8, expectedLocations7},
        {DSTimePublicDX12Gfx8, expectedLocations8},
        {DepthStencilTestBusyPublicDX12Gfx8, expectedLocations9},
        {GPUBusyPublicDX12Gfx8, expectedLocations10},
        {GPUTimePublicDX12Gfx8, expectedLocations11},
        {GSBusyPublicDX12Gfx8, expectedLocations12},
        {GSTimePublicDX12Gfx8, expectedLocations13},
        {PSBusyPublicDX12Gfx8, expectedLocations14},
        {PSTimePublicDX12Gfx8, expectedLocations15},
        {PrimitiveAssemblyBusyPublicDX12Gfx8, expectedLocations16},
        {TessellatorBusyPublicDX12Gfx8, expectedLocations17},
        {TexUnitBusyPublicDX12Gfx8, expectedLocations18},
        {HSTimePublicDX12Gfx8, expectedLocations19},
        {HSBusyPublicDX12Gfx8, expectedLocations20},
        {VSBusyPublicDX12Gfx8, expectedLocations21},
        {VSTimePublicDX12Gfx8, expectedLocations22},
    };

    VerifyCountersInPass(GPA_API_DIRECTX_12, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// GPA-83: Consolidated counter scheduler no longer schedules multi-pass public
// counters in consecutive passes  This consolidates 4 passes into 3 passes
// VSVerticeIn, GPUTime, and VSBusy should be scheduled in 3 passes
TEST(CounterDLLTests, Gpa83ThreePassTest)
{
    std::vector<uint32_t> counters = {VSVerticesInPublicDX12Gfx8, GPUTimePublicDX12Gfx8, VSBusyPublicDX12Gfx8};

    // Pass: 0  Counters: 37
    std::vector<uint32_t> expectedCountersPass0 = {2856, 3053, 3250, 3447, 2881, 3078, 3275, 3472, 2903, 3100, 3297, 3494,  2925,
                                                   3122, 3319, 3516, 2865, 3062, 3259, 3456, 2887, 3084, 3281, 3478, 49743, 87,
                                                   234,  381,  528,  68,   215,  362,  509,  163,  310,  457,  604
                                                  };

    // Pass: 1  Counters: 4
    std::vector<uint32_t> expectedCountersPass1 = {2909, 3106, 3303, 3500};

    // Pass: 2  Counters: 1
    std::vector<uint32_t> expectedCountersPass2 = {51131};

    std::vector<std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
        expectedCountersPass2,
    };

    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 23
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 29) MakeExpectedCounterLocationEntry(0, 25) MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 30) MakeExpectedCounterLocationEntry(0, 26) MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 31) MakeExpectedCounterLocationEntry(0, 27) MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 32) MakeExpectedCounterLocationEntry(0, 28) MakeExpectedCounterLocationEntry(0, 36)};

    // Pass: 1  Counters: 0
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1{MakeExpectedCounterLocationEntry(2, 0)};

    // Pass: 2  Counters: 5
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
    {
        MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 20) MakeExpectedCounterLocationEntry(0, 8) MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 5) MakeExpectedCounterLocationEntry(0, 21) MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 18) MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(1, 2) MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 19) MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 23) MakeExpectedCounterLocationEntry(0, 11) MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(0, 15) MakeExpectedCounterLocationEntry(0, 24)};

    std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
    {
        {VSVerticesInPublicDX12Gfx8, expectedLocations0}, {GPUTimePublicDX12Gfx8, expectedLocations1}, {VSBusyPublicDX12Gfx8, expectedLocations2}
    };

    VerifyCountersInPass(GPA_API_DIRECTX_12, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// SWDEV-140743: DX11 Vega L1 Cache Counters (TCP Block Instance) Always Zero
// Implemented as a test for convenience as we need to explain to the driver team the scheduling of the counters
TEST(CounterDLLTests, SwDev140743)
{
    std::vector<uint32_t> counters = {L1CacheHitCountPublicDX11Gfx9};

    // Pass: 0  Counters: 256
    std::vector<uint32_t> expectedCountersPass0 =
    {
        40677, 40762, 40847, 40932, 41017, 41102, 41187, 41272, 41357, 41442, 41527, 41612, 41697, 41782, 41867, 41952, 42037, 42122, 42207, 42292,
        42377, 42462, 42547, 42632, 42717, 42802, 42887, 42972, 43057, 43142, 43227, 43312, 43397, 43482, 43567, 43652, 43737, 43822, 43907, 43992,
        44077, 44162, 44247, 44332, 44417, 44502, 44587, 44672, 44757, 44842, 44927, 45012, 45097, 45182, 45267, 45352, 45437, 45522, 45607, 45692,
        45777, 45862, 45947, 46032, 40686, 40771, 40856, 40941, 41026, 41111, 41196, 41281, 41366, 41451, 41536, 41621, 41706, 41791, 41876, 41961,
        42046, 42131, 42216, 42301, 42386, 42471, 42556, 42641, 42726, 42811, 42896, 42981, 43066, 43151, 43236, 43321, 43406, 43491, 43576, 43661,
        43746, 43831, 43916, 44001, 44086, 44171, 44256, 44341, 44426, 44511, 44596, 44681, 44766, 44851, 44936, 45021, 45106, 45191, 45276, 45361,
        45446, 45531, 45616, 45701, 45786, 45871, 45956, 46041, 40687, 40772, 40857, 40942, 41027, 41112, 41197, 41282, 41367, 41452, 41537, 41622,
        41707, 41792, 41877, 41962, 42047, 42132, 42217, 42302, 42387, 42472, 42557, 42642, 42727, 42812, 42897, 42982, 43067, 43152, 43237, 43322,
        43407, 43492, 43577, 43662, 43747, 43832, 43917, 44002, 44087, 44172, 44257, 44342, 44427, 44512, 44597, 44682, 44767, 44852, 44937, 45022,
        45107, 45192, 45277, 45362, 45447, 45532, 45617, 45702, 45787, 45872, 45957, 46042, 40688, 40773, 40858, 40943, 41028, 41113, 41198, 41283,
        41368, 41453, 41538, 41623, 41708, 41793, 41878, 41963, 42048, 42133, 42218, 42303, 42388, 42473, 42558, 42643, 42728, 42813, 42898, 42983,
        43068, 43153, 43238, 43323, 43408, 43493, 43578, 43663, 43748, 43833, 43918, 44003, 44088, 44173, 44258, 44343, 44428, 44513, 44598, 44683,
        44768, 44853, 44938, 45023, 45108, 45193, 45278, 45363, 45448, 45533, 45618, 45703, 45788, 45873, 45958, 46043
    };

    // Pass: 1  Counters: 64
    std::vector<uint32_t> expectedCountersPass1 =
    {
        40689, 40774, 40859, 40944, 41029, 41114, 41199, 41284, 41369, 41454, 41539, 41624, 41709, 41794, 41879, 41964,
        42049, 42134, 42219, 42304, 42389, 42474, 42559, 42644, 42729, 42814, 42899, 42984, 43069, 43154, 43239, 43324,
        43409, 43494, 43579, 43664, 43749, 43834, 43919, 44004, 44089, 44174, 44259, 44344, 44429, 44514, 44599, 44684,
        44769, 44854, 44939, 45024, 45109, 45194, 45279, 45364, 45449, 45534, 45619, 45704, 45789, 45874, 45959, 46044,
    };

    std::vector<std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
    };

    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 64)
        MakeExpectedCounterLocationEntry(0, 128)
        MakeExpectedCounterLocationEntry(0, 192)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 65)
        MakeExpectedCounterLocationEntry(0, 129)
        MakeExpectedCounterLocationEntry(0, 193)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 66)
        MakeExpectedCounterLocationEntry(0, 130)
        MakeExpectedCounterLocationEntry(0, 194)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 67)
        MakeExpectedCounterLocationEntry(0, 131)
        MakeExpectedCounterLocationEntry(0, 195)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 68)
        MakeExpectedCounterLocationEntry(0, 132)
        MakeExpectedCounterLocationEntry(0, 196)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 69)
        MakeExpectedCounterLocationEntry(0, 133)
        MakeExpectedCounterLocationEntry(0, 197)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 70)
        MakeExpectedCounterLocationEntry(0, 134)
        MakeExpectedCounterLocationEntry(0, 198)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 71)
        MakeExpectedCounterLocationEntry(0, 135)
        MakeExpectedCounterLocationEntry(0, 199)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 72)
        MakeExpectedCounterLocationEntry(0, 136)
        MakeExpectedCounterLocationEntry(0, 200)
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 73)
        MakeExpectedCounterLocationEntry(0, 137)
        MakeExpectedCounterLocationEntry(0, 201)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 74)
        MakeExpectedCounterLocationEntry(0, 138)
        MakeExpectedCounterLocationEntry(0, 202)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 75)
        MakeExpectedCounterLocationEntry(0, 139)
        MakeExpectedCounterLocationEntry(0, 203)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 76)
        MakeExpectedCounterLocationEntry(0, 140)
        MakeExpectedCounterLocationEntry(0, 204)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 77)
        MakeExpectedCounterLocationEntry(0, 141)
        MakeExpectedCounterLocationEntry(0, 205)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 78)
        MakeExpectedCounterLocationEntry(0, 142)
        MakeExpectedCounterLocationEntry(0, 206)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 79)
        MakeExpectedCounterLocationEntry(0, 143)
        MakeExpectedCounterLocationEntry(0, 207)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 80)
        MakeExpectedCounterLocationEntry(0, 144)
        MakeExpectedCounterLocationEntry(0, 208)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 81)
        MakeExpectedCounterLocationEntry(0, 145)
        MakeExpectedCounterLocationEntry(0, 209)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 82)
        MakeExpectedCounterLocationEntry(0, 146)
        MakeExpectedCounterLocationEntry(0, 210)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 83)
        MakeExpectedCounterLocationEntry(0, 147)
        MakeExpectedCounterLocationEntry(0, 211)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 84)
        MakeExpectedCounterLocationEntry(0, 148)
        MakeExpectedCounterLocationEntry(0, 212)
        MakeExpectedCounterLocationEntry(1, 20)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 85)
        MakeExpectedCounterLocationEntry(0, 149)
        MakeExpectedCounterLocationEntry(0, 213)
        MakeExpectedCounterLocationEntry(1, 21)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 86)
        MakeExpectedCounterLocationEntry(0, 150)
        MakeExpectedCounterLocationEntry(0, 214)
        MakeExpectedCounterLocationEntry(1, 22)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 87)
        MakeExpectedCounterLocationEntry(0, 151)
        MakeExpectedCounterLocationEntry(0, 215)
        MakeExpectedCounterLocationEntry(1, 23)
        MakeExpectedCounterLocationEntry(0, 24)
        MakeExpectedCounterLocationEntry(0, 88)
        MakeExpectedCounterLocationEntry(0, 152)
        MakeExpectedCounterLocationEntry(0, 216)
        MakeExpectedCounterLocationEntry(1, 24)
        MakeExpectedCounterLocationEntry(0, 25)
        MakeExpectedCounterLocationEntry(0, 89)
        MakeExpectedCounterLocationEntry(0, 153)
        MakeExpectedCounterLocationEntry(0, 217)
        MakeExpectedCounterLocationEntry(1, 25)
        MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 90)
        MakeExpectedCounterLocationEntry(0, 154)
        MakeExpectedCounterLocationEntry(0, 218)
        MakeExpectedCounterLocationEntry(1, 26)
        MakeExpectedCounterLocationEntry(0, 27)
        MakeExpectedCounterLocationEntry(0, 91)
        MakeExpectedCounterLocationEntry(0, 155)
        MakeExpectedCounterLocationEntry(0, 219)
        MakeExpectedCounterLocationEntry(1, 27)
        MakeExpectedCounterLocationEntry(0, 28)
        MakeExpectedCounterLocationEntry(0, 92)
        MakeExpectedCounterLocationEntry(0, 156)
        MakeExpectedCounterLocationEntry(0, 220)
        MakeExpectedCounterLocationEntry(1, 28)
        MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 93)
        MakeExpectedCounterLocationEntry(0, 157)
        MakeExpectedCounterLocationEntry(0, 221)
        MakeExpectedCounterLocationEntry(1, 29)
        MakeExpectedCounterLocationEntry(0, 30)
        MakeExpectedCounterLocationEntry(0, 94)
        MakeExpectedCounterLocationEntry(0, 158)
        MakeExpectedCounterLocationEntry(0, 222)
        MakeExpectedCounterLocationEntry(1, 30)
        MakeExpectedCounterLocationEntry(0, 31)
        MakeExpectedCounterLocationEntry(0, 95)
        MakeExpectedCounterLocationEntry(0, 159)
        MakeExpectedCounterLocationEntry(0, 223)
        MakeExpectedCounterLocationEntry(1, 31)
        MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 96)
        MakeExpectedCounterLocationEntry(0, 160)
        MakeExpectedCounterLocationEntry(0, 224)
        MakeExpectedCounterLocationEntry(1, 32)
        MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 97)
        MakeExpectedCounterLocationEntry(0, 161)
        MakeExpectedCounterLocationEntry(0, 225)
        MakeExpectedCounterLocationEntry(1, 33)
        MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 98)
        MakeExpectedCounterLocationEntry(0, 162)
        MakeExpectedCounterLocationEntry(0, 226)
        MakeExpectedCounterLocationEntry(1, 34)
        MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 99)
        MakeExpectedCounterLocationEntry(0, 163)
        MakeExpectedCounterLocationEntry(0, 227)
        MakeExpectedCounterLocationEntry(1, 35)
        MakeExpectedCounterLocationEntry(0, 36)
        MakeExpectedCounterLocationEntry(0, 100)
        MakeExpectedCounterLocationEntry(0, 164)
        MakeExpectedCounterLocationEntry(0, 228)
        MakeExpectedCounterLocationEntry(1, 36)
        MakeExpectedCounterLocationEntry(0, 37)
        MakeExpectedCounterLocationEntry(0, 101)
        MakeExpectedCounterLocationEntry(0, 165)
        MakeExpectedCounterLocationEntry(0, 229)
        MakeExpectedCounterLocationEntry(1, 37)
        MakeExpectedCounterLocationEntry(0, 38)
        MakeExpectedCounterLocationEntry(0, 102)
        MakeExpectedCounterLocationEntry(0, 166)
        MakeExpectedCounterLocationEntry(0, 230)
        MakeExpectedCounterLocationEntry(1, 38)
        MakeExpectedCounterLocationEntry(0, 39)
        MakeExpectedCounterLocationEntry(0, 103)
        MakeExpectedCounterLocationEntry(0, 167)
        MakeExpectedCounterLocationEntry(0, 231)
        MakeExpectedCounterLocationEntry(1, 39)
        MakeExpectedCounterLocationEntry(0, 40)
        MakeExpectedCounterLocationEntry(0, 104)
        MakeExpectedCounterLocationEntry(0, 168)
        MakeExpectedCounterLocationEntry(0, 232)
        MakeExpectedCounterLocationEntry(1, 40)
        MakeExpectedCounterLocationEntry(0, 41)
        MakeExpectedCounterLocationEntry(0, 105)
        MakeExpectedCounterLocationEntry(0, 169)
        MakeExpectedCounterLocationEntry(0, 233)
        MakeExpectedCounterLocationEntry(1, 41)
        MakeExpectedCounterLocationEntry(0, 42)
        MakeExpectedCounterLocationEntry(0, 106)
        MakeExpectedCounterLocationEntry(0, 170)
        MakeExpectedCounterLocationEntry(0, 234)
        MakeExpectedCounterLocationEntry(1, 42)
        MakeExpectedCounterLocationEntry(0, 43)
        MakeExpectedCounterLocationEntry(0, 107)
        MakeExpectedCounterLocationEntry(0, 171)
        MakeExpectedCounterLocationEntry(0, 235)
        MakeExpectedCounterLocationEntry(1, 43)
        MakeExpectedCounterLocationEntry(0, 44)
        MakeExpectedCounterLocationEntry(0, 108)
        MakeExpectedCounterLocationEntry(0, 172)
        MakeExpectedCounterLocationEntry(0, 236)
        MakeExpectedCounterLocationEntry(1, 44)
        MakeExpectedCounterLocationEntry(0, 45)
        MakeExpectedCounterLocationEntry(0, 109)
        MakeExpectedCounterLocationEntry(0, 173)
        MakeExpectedCounterLocationEntry(0, 237)
        MakeExpectedCounterLocationEntry(1, 45)
        MakeExpectedCounterLocationEntry(0, 46)
        MakeExpectedCounterLocationEntry(0, 110)
        MakeExpectedCounterLocationEntry(0, 174)
        MakeExpectedCounterLocationEntry(0, 238)
        MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(0, 47)
        MakeExpectedCounterLocationEntry(0, 111)
        MakeExpectedCounterLocationEntry(0, 175)
        MakeExpectedCounterLocationEntry(0, 239)
        MakeExpectedCounterLocationEntry(1, 47)
        MakeExpectedCounterLocationEntry(0, 48)
        MakeExpectedCounterLocationEntry(0, 112)
        MakeExpectedCounterLocationEntry(0, 176)
        MakeExpectedCounterLocationEntry(0, 240)
        MakeExpectedCounterLocationEntry(1, 48)
        MakeExpectedCounterLocationEntry(0, 49)
        MakeExpectedCounterLocationEntry(0, 113)
        MakeExpectedCounterLocationEntry(0, 177)
        MakeExpectedCounterLocationEntry(0, 241)
        MakeExpectedCounterLocationEntry(1, 49)
        MakeExpectedCounterLocationEntry(0, 50)
        MakeExpectedCounterLocationEntry(0, 114)
        MakeExpectedCounterLocationEntry(0, 178)
        MakeExpectedCounterLocationEntry(0, 242)
        MakeExpectedCounterLocationEntry(1, 50)
        MakeExpectedCounterLocationEntry(0, 51)
        MakeExpectedCounterLocationEntry(0, 115)
        MakeExpectedCounterLocationEntry(0, 179)
        MakeExpectedCounterLocationEntry(0, 243)
        MakeExpectedCounterLocationEntry(1, 51)
        MakeExpectedCounterLocationEntry(0, 52)
        MakeExpectedCounterLocationEntry(0, 116)
        MakeExpectedCounterLocationEntry(0, 180)
        MakeExpectedCounterLocationEntry(0, 244)
        MakeExpectedCounterLocationEntry(1, 52)
        MakeExpectedCounterLocationEntry(0, 53)
        MakeExpectedCounterLocationEntry(0, 117)
        MakeExpectedCounterLocationEntry(0, 181)
        MakeExpectedCounterLocationEntry(0, 245)
        MakeExpectedCounterLocationEntry(1, 53)
        MakeExpectedCounterLocationEntry(0, 54)
        MakeExpectedCounterLocationEntry(0, 118)
        MakeExpectedCounterLocationEntry(0, 182)
        MakeExpectedCounterLocationEntry(0, 246)
        MakeExpectedCounterLocationEntry(1, 54)
        MakeExpectedCounterLocationEntry(0, 55)
        MakeExpectedCounterLocationEntry(0, 119)
        MakeExpectedCounterLocationEntry(0, 183)
        MakeExpectedCounterLocationEntry(0, 247)
        MakeExpectedCounterLocationEntry(1, 55)
        MakeExpectedCounterLocationEntry(0, 56)
        MakeExpectedCounterLocationEntry(0, 120)
        MakeExpectedCounterLocationEntry(0, 184)
        MakeExpectedCounterLocationEntry(0, 248)
        MakeExpectedCounterLocationEntry(1, 56)
        MakeExpectedCounterLocationEntry(0, 57)
        MakeExpectedCounterLocationEntry(0, 121)
        MakeExpectedCounterLocationEntry(0, 185)
        MakeExpectedCounterLocationEntry(0, 249)
        MakeExpectedCounterLocationEntry(1, 57)
        MakeExpectedCounterLocationEntry(0, 58)
        MakeExpectedCounterLocationEntry(0, 122)
        MakeExpectedCounterLocationEntry(0, 186)
        MakeExpectedCounterLocationEntry(0, 250)
        MakeExpectedCounterLocationEntry(1, 58)
        MakeExpectedCounterLocationEntry(0, 59)
        MakeExpectedCounterLocationEntry(0, 123)
        MakeExpectedCounterLocationEntry(0, 187)
        MakeExpectedCounterLocationEntry(0, 251)
        MakeExpectedCounterLocationEntry(1, 59)
        MakeExpectedCounterLocationEntry(0, 60)
        MakeExpectedCounterLocationEntry(0, 124)
        MakeExpectedCounterLocationEntry(0, 188)
        MakeExpectedCounterLocationEntry(0, 252)
        MakeExpectedCounterLocationEntry(1, 60)
        MakeExpectedCounterLocationEntry(0, 61)
        MakeExpectedCounterLocationEntry(0, 125)
        MakeExpectedCounterLocationEntry(0, 189)
        MakeExpectedCounterLocationEntry(0, 253)
        MakeExpectedCounterLocationEntry(1, 61)
        MakeExpectedCounterLocationEntry(0, 62)
        MakeExpectedCounterLocationEntry(0, 126)
        MakeExpectedCounterLocationEntry(0, 190)
        MakeExpectedCounterLocationEntry(0, 254)
        MakeExpectedCounterLocationEntry(1, 62)
        MakeExpectedCounterLocationEntry(0, 63)
        MakeExpectedCounterLocationEntry(0, 127)
        MakeExpectedCounterLocationEntry(0, 191)
        MakeExpectedCounterLocationEntry(0, 255)
        MakeExpectedCounterLocationEntry(1, 63)
    };

    std::map<uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations = {{L1CacheHitCountPublicDX11Gfx9, expectedLocations0}};

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx9, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// clang-format on

#endif  // _WIN32

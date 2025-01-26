#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include "angularvelocitycalculator.h"

namespace UnitTest
{
    TEST_CLASS(AngularVelocityTest)
    {
    public:
        TEST_METHOD(TestAngularVelocityBasic)
        {
            point_t points[] = {
                {0.0f, 0.0f, 0.0f},
                {1.0f, 1.0f, 1.0f},
                {2.0f, 2.0f, 2.0f}
            };
            float result = computeMaximumAngularVelocity(points, 3);
            Assert::AreEqual(1.73205081f, result, 0.0001f, L"Basic test failed");
        }

        TEST_METHOD(TestAngularVelocitySinglePoint)
        {
            point_t points[] = {
                {0.0f, 0.0f, 0.0f}
            };
            auto func = [&]() { computeMaximumAngularVelocity(points, 1); };
            Assert::ExpectException<std::invalid_argument>(func, L"Single point test failed");
        }

        TEST_METHOD(TestAngularVelocityZeroDeltaTime)
        {
            point_t points[] = {
                {0.0f, 0.0f, 0.0f},
                {1.0f, 1.0f, 0.0f}
            };
            auto func = [&]() { computeMaximumAngularVelocity(points, 2); };
            Assert::ExpectException<std::invalid_argument>(func, L"Zero delta time test failed");
        }

        TEST_METHOD(TestAngularVelocityNegativeTime)
        {
            point_t points[] = {
                {0.0f, 0.0f, 1.0f},
                {1.0f, 1.0f, 0.0f}
            };
            float result = computeMaximumAngularVelocity(points, 2);
            Assert::AreEqual(1.41421356f, result, 0.0001f, L"Negative time test failed");
        }

        TEST_METHOD(TestAngularVelocityMultiplePoints)
        {
            point_t points[] = {
                {0.0f, 0.0f, 0.0f},
                {1.0f, 1.0f, 1.0f},
                {2.0f, 2.0f, 2.0f},
                {3.0f, 3.0f, 3.0f}
            };
            float result = computeMaximumAngularVelocity(points, 4);
            Assert::AreEqual(1.73205081f, result, 0.0001f, L"Multiple points test failed");
        }

        TEST_METHOD(TestAngularVelocityNegativeCoordinates)
        {
            point_t points[] = {
                {-1.0f, -1.0f, -1.0f},
                {-2.0f, -2.0f, -2.0f},
                {-3.0f, -3.0f, -3.0f}
            };
            float result = computeMaximumAngularVelocity(points, 3);
            Assert::AreEqual(1.73205081f, result, 0.0001f, L"Negative coordinates test failed");
        }
       
        TEST_METHOD(TestAngularVelocityClosePoints)
        {
            point_t points[] = {
                {0.0f, 0.0f, 0.0f},
                {0.1f, 0.1f, 0.1f},
                {0.2f, 0.2f, 0.2f}
            };
            float result = computeMaximumAngularVelocity(points, 3);
            Assert::AreEqual(0.17320508f, result, 0.0001f, L"Close points test failed");
        }

        TEST_METHOD(TestAngularVelocityManyPoints)
        {
            const int numPoints = 1000;
            point_t points[numPoints];
            for (int i = 0; i < numPoints; ++i)
            {
                points[i] = { static_cast<float>(i), static_cast<float>(i), static_cast<float>(i) };
            }
            float result = computeMaximumAngularVelocity(points, numPoints);
            Assert::IsTrue(result > 0.0f, L"Many points test failed");
        }
    };
}

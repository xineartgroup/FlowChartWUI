#pragma once

#include <vector>
#include <cmath>

namespace FlowChart
{
	namespace Data
	{
		class Spline2D
		{
		private:
			static std::vector<winrt::Windows::Foundation::Point> bezierPoints;

			/// <summary>
			/// recreate the bezier curve.
			/// </summary>
			/// <param name="ctrl1">first initial point</param>
			/// <param name="ctrl2">second initial point</param>
			/// <param name="ctrl3">third initial point</param>
			/// <param name="iterations">number of iteration of the algorithm</param>
			/// <returns>the list of points in the curve</returns>
			static void ReCalculate(winrt::Windows::Foundation::Point ctrl1, winrt::Windows::Foundation::Point ctrl2, winrt::Windows::Foundation::Point ctrl3, int iteration);

			/// <summary>
			/// create a bezier curve
			/// </summary>
			/// <param name="ctrl1">first initial point</param>
			/// <param name="ctrl2">second initial point</param>
			/// <param name="ctrl3">third initial point</param>
			static void CreateBezier(winrt::Windows::Foundation::Point ctrl1, winrt::Windows::Foundation::Point ctrl2, winrt::Windows::Foundation::Point ctrl3, int iterations);

			/// <summary>
			/// Recursivly call to construct the bezier curve with control points
			/// </summary>
			/// <param name="ctrl1">first control point of bezier curve segment</param>
			/// <param name="ctrl2">second control point of bezier curve segment</param>
			/// <param name="ctrl3">third control point of bezier curve segment</param>
			/// <param name="currentIteration">the current interation of a branch</param>
			static void PopulateBezierPoints(winrt::Windows::Foundation::Point ctrl1, winrt::Windows::Foundation::Point ctrl2, winrt::Windows::Foundation::Point ctrl3, int currentIteration, int iterations);

			/// <summary>
			/// Find mid point
			/// </summary>
			/// <param name="controlPoint1">first control point</param>
			/// <param name="controlPoint2">second control point</param>
			/// <returns></returns>
			static winrt::Windows::Foundation::Point MidPoint(winrt::Windows::Foundation::Point controlPoint1, winrt::Windows::Foundation::Point controlPoint2);

		public:
			static int SpaceCount;
			static bool Smoothing;

			/// <summary>
			/// Gets a list of all points
			/// </summary>
			/// <returns></returns>
			static std::vector<winrt::Windows::Foundation::Point> GetBezierPoints(std::vector<winrt::Windows::Foundation::Point> points, int iterations);

			/// <summary>
			/// Gets a list of all points
			/// </summary>
			/// <returns></returns>
			static std::vector<winrt::Windows::Foundation::Point> GetMidPoints(std::vector<winrt::Windows::Foundation::Point> points, float weight);

			/// <summary>
			/// 
			/// </summary>
			static std::vector<winrt::Windows::Foundation::Point> Spline2D::GetSpline(std::vector<winrt::Windows::Foundation::Point> points);
		};
	}
}

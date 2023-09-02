#include "pch.h"
#include "Spline2D.h"

namespace FlowChart
{
	namespace Data
	{
		std::vector<winrt::Windows::Foundation::Point> Spline2D::bezierPoints;
		int Spline2D::SpaceCount = 0;
		bool Spline2D::Smoothing = false;

		void Spline2D::ReCalculate(winrt::Windows::Foundation::Point ctrl1, winrt::Windows::Foundation::Point ctrl2, winrt::Windows::Foundation::Point ctrl3, int iterations)
		{
			CreateBezier(ctrl1, ctrl2, ctrl3, iterations);
		}

		void Spline2D::CreateBezier(winrt::Windows::Foundation::Point ctrl1, winrt::Windows::Foundation::Point ctrl2, winrt::Windows::Foundation::Point ctrl3, int iterations)
		{
			bezierPoints.push_back(ctrl1); // add the first control point
			PopulateBezierPoints(ctrl1, ctrl2, ctrl3, 0, iterations);
			bezierPoints.push_back(ctrl3); // add the last control point
		}

		void Spline2D::PopulateBezierPoints(winrt::Windows::Foundation::Point ctrl1, winrt::Windows::Foundation::Point ctrl2, winrt::Windows::Foundation::Point ctrl3, int currentIteration, int iterations)
		{
			if (currentIteration < iterations)
			{
				//calculate next mid points
				winrt::Windows::Foundation::Point midPoint1 = MidPoint(ctrl1, ctrl2);
				winrt::Windows::Foundation::Point midPoint2 = MidPoint(ctrl2, ctrl3);
				winrt::Windows::Foundation::Point midPoint3 = MidPoint(midPoint1, midPoint2); //the next control point
				++currentIteration;
				PopulateBezierPoints(ctrl1, midPoint1, midPoint3, currentIteration, iterations); //left branch
				bezierPoints.push_back(midPoint3); //add the next control point
				PopulateBezierPoints(midPoint3, midPoint2, ctrl3, currentIteration, iterations); //right branch
			}
		}

		winrt::Windows::Foundation::Point Spline2D::MidPoint(winrt::Windows::Foundation::Point controlPoint1, winrt::Windows::Foundation::Point controlPoint2)
		{
			float x = (controlPoint1.X + controlPoint2.X) * 0.5f;
			float y = (controlPoint1.Y + controlPoint2.Y) * 0.5f;
			return winrt::Windows::Foundation::Point(x, y);
		}

		std::vector<winrt::Windows::Foundation::Point> Spline2D::GetBezierPoints(std::vector<winrt::Windows::Foundation::Point> points, int iterations)
		{
			bezierPoints.clear();
			size_t i = 1;
			while (i < points.size() - 1)
			{
				ReCalculate(points[i - 1], points[i], points[i + 1], iterations);
				i += (2 + SpaceCount);
			}
			if (i - 1 < points.size())
				bezierPoints.push_back(points[points.size() - 1]);
			return bezierPoints;
		}

		std::vector<winrt::Windows::Foundation::Point> Spline2D::GetMidPoints(std::vector<winrt::Windows::Foundation::Point> points, float weight)
		{
			std::vector<winrt::Windows::Foundation::Point> result = std::vector<winrt::Windows::Foundation::Point>();

			for (size_t i = 0; i < points.size() - 1; i++)
			{
				winrt::Windows::Foundation::Point point1 = points[i];
				winrt::Windows::Foundation::Point point2 = points[i + 1];
				float x1 = (point1.X == point2.X) ? point1.X : (point1.X < point2.X) ? point1.X + weight : point2.X + weight;
				float y1 = (point1.Y == point2.Y) ? point1.Y : (point1.Y < point2.Y) ? point1.Y + weight : point2.Y + weight;
				float x2 = (point1.X == point2.X) ? point2.X : (point1.X < point2.X) ? point2.X - weight : point1.X - weight;
				float y2 = (point1.Y == point2.Y) ? point2.Y : (point1.Y < point2.Y) ? point2.Y - weight : point1.Y - weight;

				winrt::Windows::Foundation::Point pointA(x1, y1);
				winrt::Windows::Foundation::Point pointB(x2, y2);

				if (i == 0)
				{
					result.push_back(points[i]);
				}

				if ((point1.X == pointA.X && point1.Y < pointA.Y) ||
					(point1.Y == pointA.Y && point1.X < pointA.X))
				{
					result.push_back(points[i]);
					result.push_back(pointA);
					result.push_back(pointB);
				}
				else
				{
					result.push_back(points[i]);
					result.push_back(pointB);
					result.push_back(pointA);
				}

				if (i + 1 == points.size() - 1)
				{
					result.push_back(points[i + 1]);
				}
			}

			return result;
		}

		std::vector<winrt::Windows::Foundation::Point> Spline2D::GetSpline(std::vector<winrt::Windows::Foundation::Point> points)
		{
			SpaceCount = 1;
			points = Spline2D::GetMidPoints(points, 9.0f);
			points = Spline2D::GetBezierPoints(points, 3);
			return points;
		}
	}
}

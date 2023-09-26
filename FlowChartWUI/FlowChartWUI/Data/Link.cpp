#include "pch.h"
#include "Link.h"

namespace FlowChart
{
	namespace Data
	{

		Link::Link()
		{
			MARGIN = 30.0f;
			linkPoints = std::vector<winrt::Windows::Foundation::Point>();
			IsHover = false;
			IsSelected = false;
			InputAnchorIndex = 0;
			OutputAnchorIndex = 0;
			NextSymbol = NULL;
			ParentSymbol = NULL;
		}

		bool Link::IsHit()
		{
			std::vector<winrt::Windows::Foundation::Point> points = std::vector<winrt::Windows::Foundation::Point>();
			for (int i = -2; i <= 2; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					points.push_back(winrt::Windows::Foundation::Point(Utility::MousePosition.X + i, Utility::MousePosition.Y + j));
				}
			}

			for (int i = 0; i < linkPoints.size(); i++)
			{
				for (std::vector<winrt::Windows::Foundation::Point>::const_iterator point = points.begin(); point != points.end(); ++point)
				{
					//if (point.X == linkPoints[i].X &&
					//    point.X == linkPoints[i].X &&
					//    point.Y == linkPoints[i].Y &&
					//    point.Y == linkPoints[i].Y)
					//{
					//    return true;
					//}

					if (i + 1 < linkPoints.size())
					{
						double dxl = linkPoints[i + 1].X - linkPoints[i].X;
						double dyl = linkPoints[i + 1].Y - linkPoints[i].Y;

						double dxc = point->X - linkPoints[i].X;
						double dyc = point->Y - linkPoints[i].Y;

						if (!(dxl == 0 && dyl == 0))
						{
							double cross = dxc * dyl - dyc * dxl;

							if (cross == 0.0)
							{
								if (abs(dxl) >= abs(dyl))
								{
									return dxl > 0 ? linkPoints[i].X <= point->X && point->X <= linkPoints[i + 1].X : linkPoints[i + 1].X <= point->X && point->X <= linkPoints[i].X;
								}
								else
								{
									return dyl > 0 ? linkPoints[i].Y <= point->Y && point->Y <= linkPoints[i + 1].Y : linkPoints[i + 1].Y <= point->Y && point->Y <= linkPoints[i].Y;
								}
							}
						}
					}
				}
			}
			return false;
		}

		void Link::Draw(Canvas canvas)
		{
			SetLinkPoints(true);

			if (ParentSymbol && NextSymbol)
			{
				if (linkPoints.size() > 0)
				{
					size_t defaultIndex = 0;
					std::vector<AnchorPoint*> anchorPoints = NextSymbol->GetInputAnchorPoints();
					for (size_t i = 0; i < anchorPoints.size(); i++)
					{
						if (anchorPoints[i]->getPlacement() == LinkAnchorPlacement::Top)
						{
							defaultIndex = i;
							break;
						}
					}

					AnchorPoint* anchorPoint1 = NextSymbol->GetInputAnchorPoint(InputAnchorIndex < 0 ? (int)defaultIndex : InputAnchorIndex);

					if (anchorPoint1)
					{
						LinkAnchorPlacement direction2 = anchorPoint1->getPlacement();

						PathGeometry myPathGeometry1;

						PathFigure pathFigure1;
						pathFigure1.StartPoint(linkPoints[0]);
						for (size_t i = 1; i < linkPoints.size(); i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(linkPoints[i]);
							pathFigure1.Segments().Append(lineSegment);
						}
						myPathGeometry1.Figures().Append(pathFigure1);

						DoubleCollection strokeDashArray;

						if (Stroke == StrokeStyle::Dashed)
						{
							strokeDashArray.Append(5);
							strokeDashArray.Append(5);
						}
						else if (Stroke == StrokeStyle::Dotted)
						{
							strokeDashArray.Append(1);
							strokeDashArray.Append(5);
						}

						winrt::Microsoft::UI::Xaml::Shapes::Path path1;
						path1.Stroke(SolidColorBrush(IsSelected || IsHover ? winrt::Windows::UI::Colors::Brown() : Utility::BrushFlow));
						path1.StrokeThickness(StrokeSize);
						path1.StrokeDashArray(strokeDashArray);
						path1.Data(myPathGeometry1);
						canvas.Children().Append(path1);

						//Draw the arrow
						winrt::Windows::Foundation::Point arrowPoints[4];

						if (direction2 == Top)
						{
							arrowPoints[0].X = linkPoints[linkPoints.size() - 1].X - Utility::HALFLINK;
							arrowPoints[0].Y = linkPoints[linkPoints.size() - 1].Y - (Utility::HALFLINK * 2);
							arrowPoints[1].X = linkPoints[linkPoints.size() - 1].X;
							arrowPoints[1].Y = linkPoints[linkPoints.size() - 1].Y;
							arrowPoints[2].X = linkPoints[linkPoints.size() - 1].X + Utility::HALFLINK;
							arrowPoints[2].Y = linkPoints[linkPoints.size() - 1].Y - (Utility::HALFLINK * 2);
							arrowPoints[3].X = arrowPoints[0].X;
							arrowPoints[3].Y = arrowPoints[0].Y;
						}
						else if (direction2 == Left)
						{
							arrowPoints[0].X = linkPoints[linkPoints.size() - 1].X - (Utility::HALFLINK * 2);
							arrowPoints[0].Y = linkPoints[linkPoints.size() - 1].Y - Utility::HALFLINK;
							arrowPoints[1].X = linkPoints[linkPoints.size() - 1].X;
							arrowPoints[1].Y = linkPoints[linkPoints.size() - 1].Y;
							arrowPoints[2].X = linkPoints[linkPoints.size() - 1].X - (Utility::HALFLINK * 2);
							arrowPoints[2].Y = linkPoints[linkPoints.size() - 1].Y + Utility::HALFLINK;
							arrowPoints[3].X = arrowPoints[0].X;
							arrowPoints[3].Y = arrowPoints[0].Y;
						}
						else if (direction2 == Right)
						{
							arrowPoints[0].X = linkPoints[linkPoints.size() - 1].X + (Utility::HALFLINK * 2);
							arrowPoints[0].Y = linkPoints[linkPoints.size() - 1].Y + Utility::HALFLINK;
							arrowPoints[1].X = linkPoints[linkPoints.size() - 1].X;
							arrowPoints[1].Y = linkPoints[linkPoints.size() - 1].Y;
							arrowPoints[2].X = linkPoints[linkPoints.size() - 1].X + (Utility::HALFLINK * 2);
							arrowPoints[2].Y = linkPoints[linkPoints.size() - 1].Y - Utility::HALFLINK;
							arrowPoints[3].X = arrowPoints[0].X;
							arrowPoints[3].Y = arrowPoints[0].Y;
						}
						else if (direction2 == Bottom)
						{
							arrowPoints[0].X = linkPoints[linkPoints.size() - 1].X + Utility::HALFLINK;
							arrowPoints[0].Y = linkPoints[linkPoints.size() - 1].Y + (Utility::HALFLINK * 2);
							arrowPoints[1].X = linkPoints[linkPoints.size() - 1].X;
							arrowPoints[1].Y = linkPoints[linkPoints.size() - 1].Y;
							arrowPoints[2].X = linkPoints[linkPoints.size() - 1].X - Utility::HALFLINK;
							arrowPoints[2].Y = linkPoints[linkPoints.size() - 1].Y + (Utility::HALFLINK * 2);
							arrowPoints[3].X = arrowPoints[0].X;
							arrowPoints[3].Y = arrowPoints[0].Y;
						}
						else
						{
							if (linkPoints.size() > 1)
							{
								if (linkPoints[linkPoints.size() - 1].X > linkPoints[linkPoints.size() - 2].X)
								{
									arrowPoints[0].X = linkPoints[linkPoints.size() - 1].X - (Utility::HALFLINK * 2);
									arrowPoints[0].Y = linkPoints[linkPoints.size() - 1].Y - Utility::HALFLINK;
									arrowPoints[1].X = linkPoints[linkPoints.size() - 1].X;
									arrowPoints[1].Y = linkPoints[linkPoints.size() - 1].Y;
									arrowPoints[2].X = linkPoints[linkPoints.size() - 1].X - (Utility::HALFLINK * 2);
									arrowPoints[2].Y = linkPoints[linkPoints.size() - 1].Y + Utility::HALFLINK;
									arrowPoints[3].X = arrowPoints[0].X;
									arrowPoints[3].Y = arrowPoints[0].Y;
								}
								else
								{
									arrowPoints[0].X = linkPoints[linkPoints.size() - 1].X + (Utility::HALFLINK * 2);
									arrowPoints[0].Y = linkPoints[linkPoints.size() - 1].Y + Utility::HALFLINK;
									arrowPoints[1].X = linkPoints[linkPoints.size() - 1].X;
									arrowPoints[1].Y = linkPoints[linkPoints.size() - 1].Y;
									arrowPoints[2].X = linkPoints[linkPoints.size() - 1].X + (Utility::HALFLINK * 2);
									arrowPoints[2].Y = linkPoints[linkPoints.size() - 1].Y - Utility::HALFLINK;
									arrowPoints[3].X = arrowPoints[0].X;
									arrowPoints[3].Y = arrowPoints[0].Y;
								}
							}
						}

						PathGeometry myPathGeometry2;

						PathFigure pathFigure2;
						pathFigure2.StartPoint(arrowPoints[0]);
						for (int i = 1; i < 4; i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(arrowPoints[i]);
							pathFigure2.Segments().Append(lineSegment);
						}
						myPathGeometry2.Figures().Append(pathFigure2);

						winrt::Microsoft::UI::Xaml::Shapes::Path path2;
						path2.Fill(SolidColorBrush(IsSelected || IsHover ? winrt::Windows::UI::Colors::Brown() : Utility::BrushFlow));
						path2.Stroke(SolidColorBrush(IsSelected || IsHover ? winrt::Windows::UI::Colors::Brown() : Utility::BrushFlow));
						path2.StrokeThickness(Utility::FlowSize);
						path2.Data(myPathGeometry2);
						canvas.Children().Append(path2);
					}
				}
			}
		}

		void Link::DrawLinking(Canvas canvas)
		{
			if (ParentSymbol)
			{
				AnchorPoint* anchorPoint = ParentSymbol->GetOutputAnchorPoint(OutputAnchorIndex);

				if (anchorPoint)
				{
					LinkAnchorPlacement direction1 = anchorPoint->getPlacement();
					winrt::Windows::Foundation::Point position = anchorPoint->getPosition();

					winrt::Windows::Foundation::Point points[6];

					if (direction1 == Bottom)
					{
						points[0].X = position.X;
						points[0].Y = position.Y;
						points[1].X = points[0].X;
						points[1].Y = points[0].Y + MARGIN;
						points[2].X = Utility::MousePosition.X;
						points[2].Y = points[1].Y;
						points[3].X = points[2].X;
						points[3].Y = Utility::MousePosition.Y > points[0].Y ? Utility::MousePosition.Y - MARGIN : Utility::MousePosition.Y;
						points[4].X = Utility::MousePosition.X;
						points[4].Y = points[3].Y;
						points[5].X = Utility::MousePosition.X;
						points[5].Y = Utility::MousePosition.Y;

						if (position.Y < Utility::MousePosition.Y)
						{
							points[2].X = points[4].X;
							points[3].X = points[4].X;
						}

						PathGeometry myPathGeometry1;

						PathFigure pathFigure1;
						pathFigure1.StartPoint(points[0]);
						for (int i = 1; i < 6; i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(points[i]);
							pathFigure1.Segments().Append(lineSegment);
						}
						myPathGeometry1.Figures().Append(pathFigure1);

						winrt::Microsoft::UI::Xaml::Shapes::Path path1;
						path1.Stroke(SolidColorBrush(Utility::BrushFlow));
						path1.StrokeThickness(Utility::FlowSize);
						path1.Data(myPathGeometry1);
						canvas.Children().Append(path1);
					}
					else if (direction1 == Top)
					{
						points[0].X = position.X;
						points[0].Y = position.Y;
						points[1].X = points[0].X;
						points[1].Y = points[0].Y - MARGIN;
						points[2].X = Utility::MousePosition.X;
						points[2].Y = points[1].Y;
						points[3].X = points[2].X;
						points[3].Y = Utility::MousePosition.Y > points[0].Y ? Utility::MousePosition.Y - MARGIN : Utility::MousePosition.Y;
						points[4].X = Utility::MousePosition.X;
						points[4].Y = points[3].Y;
						points[5].X = Utility::MousePosition.X;
						points[5].Y = Utility::MousePosition.Y;

						if (position.Y < Utility::MousePosition.Y)
						{
							points[2].X = points[4].X;
							points[3].X = points[4].X;
						}

						PathGeometry myPathGeometry1;

						PathFigure pathFigure1;
						pathFigure1.StartPoint(points[0]);
						for (int i = 1; i < 6; i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(points[i]);
							pathFigure1.Segments().Append(lineSegment);
						}
						myPathGeometry1.Figures().Append(pathFigure1);

						winrt::Microsoft::UI::Xaml::Shapes::Path path1;
						path1.Stroke(SolidColorBrush(Utility::BrushFlow));
						path1.StrokeThickness(Utility::FlowSize);
						path1.Data(myPathGeometry1);
						canvas.Children().Append(path1);
					}
					else if (direction1 == Right)
					{
						if (position.X > Utility::MousePosition.X)
						{
							points[0].X = position.X;
							points[0].Y = position.Y;
							points[1].X = points[0].X + MARGIN;
							points[1].Y = points[0].Y;
							points[2].X = points[0].X + MARGIN;
							points[2].Y = Utility::MousePosition.Y;
							points[3].X = Utility::MousePosition.X;
							points[3].Y = Utility::MousePosition.Y;
							points[4].X = points[3].X;
							points[4].Y = points[3].Y;
							points[5].X = points[4].X;
							points[5].Y = points[4].Y;
						}
						else
						{
							points[0].X = position.X;
							points[0].Y = position.Y;
							points[1].X = Utility::MousePosition.X;
							points[1].Y = position.Y;
							points[2].X = Utility::MousePosition.X;
							points[2].Y = Utility::MousePosition.Y;
							points[3].X = points[2].X;
							points[3].Y = points[2].Y;
							points[4].X = points[3].X;
							points[4].Y = points[3].Y;
							points[5].X = points[4].X;
							points[5].Y = points[4].Y;
						}

						PathGeometry myPathGeometry;

						PathFigure pathFigure;
						pathFigure.StartPoint(points[0]);
						for (int i = 1; i < 6; i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(points[i]);
							pathFigure.Segments().Append(lineSegment);
						}
						myPathGeometry.Figures().Append(pathFigure);

						winrt::Microsoft::UI::Xaml::Shapes::Path path;
						path.Stroke(SolidColorBrush(Utility::BrushFlow));
						path.StrokeThickness(Utility::FlowSize);
						path.Data(myPathGeometry);
						canvas.Children().Append(path);
					}
					else if (direction1 == Left)
					{
						if (position.X < Utility::MousePosition.X)
						{
							points[0].X = position.X;
							points[0].Y = position.Y;
							points[1].X = points[0].X - MARGIN;
							points[1].Y = points[0].Y;
							points[2].X = points[0].X - MARGIN;
							points[2].Y = Utility::MousePosition.Y;
							points[3].X = Utility::MousePosition.X;
							points[3].Y = Utility::MousePosition.Y;
							points[4].X = points[3].X;
							points[4].Y = points[3].Y;
							points[5].X = points[4].X;
							points[5].Y = points[4].Y;
						}
						else
						{
							points[0].X = position.X;
							points[0].Y = position.Y;
							points[1].X = Utility::MousePosition.X;
							points[1].Y = position.Y;
							points[2].X = Utility::MousePosition.X;
							points[2].Y = Utility::MousePosition.Y;
							points[3].X = points[2].X;
							points[3].Y = points[2].Y;
							points[4].X = points[3].X;
							points[4].Y = points[3].Y;
							points[5].X = points[4].X;
							points[5].Y = points[4].Y;
						}

						PathGeometry myPathGeometry;

						PathFigure pathFigure;
						pathFigure.StartPoint(points[0]);
						for (int i = 1; i < 6; i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(points[i]);
							pathFigure.Segments().Append(lineSegment);
						}
						myPathGeometry.Figures().Append(pathFigure);

						winrt::Microsoft::UI::Xaml::Shapes::Path path;
						path.Stroke(SolidColorBrush(Utility::BrushFlow));
						path.StrokeThickness(Utility::FlowSize);
						path.Data(myPathGeometry);
						canvas.Children().Append(path);
					}
					else
					{
						points[0].X = position.X;
						points[0].Y = position.Y;
						points[1].X = Utility::MousePosition.X;
						points[1].Y = position.Y;
						points[2].X = Utility::MousePosition.X;
						points[2].Y = Utility::MousePosition.Y;
						points[3].X = points[2].X;
						points[3].Y = points[2].Y;
						points[4].X = points[3].X;
						points[4].Y = points[3].Y;
						points[5].X = points[4].X;
						points[5].Y = points[4].Y;

						PathGeometry myPathGeometry;

						PathFigure pathFigure;
						pathFigure.StartPoint(points[0]);
						for (int i = 1; i < 6; i++)
						{
							LineSegment lineSegment;
							lineSegment.Point(points[i]);
							pathFigure.Segments().Append(lineSegment);
						}
						myPathGeometry.Figures().Append(pathFigure);

						winrt::Microsoft::UI::Xaml::Shapes::Path path;
						path.Stroke(SolidColorBrush(Utility::BrushFlow));
						path.StrokeThickness(Utility::FlowSize);
						path.Data(myPathGeometry);
						canvas.Children().Append(path);
					}
				}
			}
		}

		void Link::SetLinkPoints(bool recalculate)
		{
			if (ParentSymbol && NextSymbol)
			{
				size_t defaultIndex = 0;
				std::vector<AnchorPoint*> anchorPoints = NextSymbol->GetInputAnchorPoints();
				for (size_t i = 0; i < anchorPoints.size(); i++)
				{
					if (anchorPoints[i]->getPlacement() == LinkAnchorPlacement::Top)
					{
						defaultIndex = i;
						break;
					}
				}

				AnchorPoint* anchorPoint1 = NextSymbol->GetInputAnchorPoint(InputAnchorIndex < 0 ? (int)defaultIndex : InputAnchorIndex);
				AnchorPoint* anchorPoint = ParentSymbol->GetOutputAnchorPoint(OutputAnchorIndex);

				if (anchorPoint && anchorPoint1)
				{
					winrt::Windows::Foundation::Point point1 = anchorPoint->getPosition();
					winrt::Windows::Foundation::Point point2 = anchorPoint1->getPosition();

					LinkAnchorPlacement direction1 = anchorPoint->getPlacement();
					LinkAnchorPlacement direction2 = anchorPoint1->getPlacement();

					if (recalculate)
					{
						if (direction2 == Top)
						{
							if (direction1 == Bottom)
							{
								float minX = point1.X < point2.X ? point2.X + (3 * NextSymbol->GetWidth() / 4) : point2.X - (3 * NextSymbol->GetWidth() / 4);

								if (point1.Y < point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[1].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(minX, linkPoints[1].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[3].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[4].X, point2.Y));
								}
							}
							else if (direction1 == Right)
							{
								if (point1.X < point2.X)
								{
									if (point1.Y < point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + (NextSymbol->GetWidth() / 2) + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y - MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
									}
								}
								else
								{
									if (point1.Y < point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y + NextSymbol->GetHeight() + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - (NextSymbol->GetWidth() / 2) - MARGIN, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y - MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[4].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[5].X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y - MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
									}
								}
							}
							else if (direction1 == Left)
							{
								if (point1.X > point2.X + NextSymbol->GetWidth() + MARGIN)
								{
									if (point1.Y < point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + (NextSymbol->GetWidth() / 2) + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y - MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
									}
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, linkPoints[0].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
								}
							}
							else if (direction1 == Top)
							{
								linkPoints.clear();
								linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
								if (point1.Y > point2.Y)
								{
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point2.Y - MARGIN));
								}
								else
								{
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y - MARGIN));
								}
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[1].Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
							}
							else
							{
								if (point1.Y < point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									float pointN = point2.X < point1.X ? point2.X - (NextSymbol->GetWidth() / 2) - MARGIN : point2.X + (NextSymbol->GetWidth() / 2) + MARGIN;

									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point2.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
						}
						else if (direction2 == Left)
						{
							if (direction1 == Bottom)
							{
								if (point1.X < point2.X)
								{
									if (point1.Y < point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, point2.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
									}
									else
									{
										if (point1.X + (ParentSymbol->GetWidth() / 2) + MARGIN + MARGIN < point2.X)
										{
											linkPoints.clear();
											linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
											linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, linkPoints[1].Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
										}
										else
										{
											linkPoints.clear();
											linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
											linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + NextSymbol->GetWidth() + MARGIN, linkPoints[1].Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y - (NextSymbol->GetHeight() / 2) - MARGIN));
											linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, linkPoints[3].Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, point2.Y));
											linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
										}
									}
								}
								else
								{
									if (point1.Y < point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, linkPoints[1].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, linkPoints[1].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
									}
								}
							}
							else if (direction1 == Right)
							{
								if (point1.X < point2.X)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point1.Y + NextSymbol->GetHeight() + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, point1.Y + NextSymbol->GetHeight() + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else if (direction1 == Left)
							{
								linkPoints.clear();
								linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
								if (point2.X < point1.X)
								{
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, linkPoints[0].Y));
								}
								else
								{
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, linkPoints[0].Y));
								}
								linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
							}
							else if (direction1 == Top)
							{
								if (point2.Y + NextSymbol->GetHeight() < point1.Y && point2.X > point1.X)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, point1.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else
							{
								if (point1.X < point2.X)
								{
									float pointN = point1.X + (ParentSymbol->GetWidth() / 2) + MARGIN;

									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									float pointN = point1.X + (ParentSymbol->GetWidth() / 2) + MARGIN;
									float pointNY = point1.Y > point2.Y ? point2.Y + (ParentSymbol->GetWidth() / 2) + MARGIN : point2.Y - MARGIN;

									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, pointNY));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, pointNY));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
						}
						else if (direction2 == Right)
						{
							if (direction1 == Bottom)
							{
								if (point1.X > point2.X && point1.Y < point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + MARGIN, point1.Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else if (direction1 == Right)
							{
								float pointN = point1.X > point2.X ? point1.X + MARGIN : point2.X + MARGIN;

								linkPoints.clear();
								linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point1.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point2.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
							}
							else if (direction1 == Left)
							{
								if (point1.X > point2.X + MARGIN)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point2.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + MARGIN, point2.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else if (direction1 == Top)
							{
								if (point1.X > point2.X && point1.Y > point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + MARGIN, point1.Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else
							{
								float pointN = point1.X > point2.X + (ParentSymbol->GetWidth() / 2) + MARGIN ? point1.X - (ParentSymbol->GetWidth() / 2) - MARGIN : point2.X + MARGIN;

								linkPoints.clear();
								linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point1.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point2.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
							}
						}
						else if (direction2 == Bottom)
						{
							if (direction1 == Bottom)
							{
								linkPoints.clear();
								linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
								if (point1.Y < point2.Y)
								{
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point2.Y + MARGIN));
								}
								else
								{
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y + MARGIN));
								}
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[1].Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
							}
							else if (direction1 == Right)
							{
								if (point1.X < point2.X)
								{
									if (point1.Y > point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + (NextSymbol->GetWidth() / 2) + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
									}
								}
								else
								{
									if (point1.Y > point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y + NextSymbol->GetHeight() + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
									}
								}
							}
							else if (direction1 == Left)
							{
								if (point1.X > point2.X + NextSymbol->GetWidth() + MARGIN)
								{
									if (point1.Y > point2.Y)
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y));
									}
									else
									{
										linkPoints.clear();
										linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X + (NextSymbol->GetWidth() / 2) + MARGIN, linkPoints[0].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y + MARGIN));
										linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
										linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
									}
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, linkPoints[0].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[1].X, point2.Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[2].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[3].X, point2.Y));
								}
							}
							else if (direction1 == Top)
							{
								float minX = point1.X < point2.X ? point2.X + (3 * NextSymbol->GetWidth() / 4) : point2.X - (3 * NextSymbol->GetWidth() / 4);

								if (point1.Y > point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[1].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(minX, linkPoints[1].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, linkPoints[3].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[4].X, point2.Y));
								}
							}
							else
							{
								if (point1.Y > point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									float pointN = point2.X < point1.X ? point2.X - (NextSymbol->GetWidth() / 2) - MARGIN : point2.X + (NextSymbol->GetWidth() / 2) + MARGIN;

									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointN, point2.Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
						}
						else
						{
							if (direction1 == Bottom)
							{
								if (point1.Y < point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									float pointNX = point1.X < point2.X ? point2.X - (NextSymbol->GetWidth() / 2) - MARGIN : point2.X + (NextSymbol->GetWidth() / 2) + MARGIN;

									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointNX, linkPoints[1].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else if (direction1 == Right)
							{
								if (point1.X < point2.X)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X + MARGIN, point1.Y + NextSymbol->GetHeight() + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - (ParentSymbol->GetWidth() / 2) - MARGIN, point1.Y + NextSymbol->GetHeight() + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - (ParentSymbol->GetWidth() / 2) - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else if (direction1 == Left)
							{
								if (point1.X > point2.X)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X - MARGIN, point1.Y + NextSymbol->GetHeight() + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - (ParentSymbol->GetWidth() / 2) - MARGIN, point1.Y + NextSymbol->GetHeight() + MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X - (ParentSymbol->GetWidth() / 2) - MARGIN, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else if (direction1 == Top)
							{
								if (point1.Y > point2.Y)
								{
									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
								else
								{
									float pointNX = point1.X < point2.X ? point2.X - (NextSymbol->GetWidth() / 2) - MARGIN : point2.X + (NextSymbol->GetWidth() / 2) + MARGIN;

									linkPoints.clear();
									linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[0].X, linkPoints[0].Y - MARGIN));
									linkPoints.push_back(winrt::Windows::Foundation::Point(pointNX, linkPoints[1].Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(linkPoints[2].X, point2.Y));
									linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
								}
							}
							else
							{
								float pointNX = point1.X < point2.X ? point2.X - (NextSymbol->GetWidth() / 2) - MARGIN : point2.X + (NextSymbol->GetWidth() / 2) + MARGIN;

								linkPoints.clear();
								linkPoints.push_back(winrt::Windows::Foundation::Point(point1.X, point1.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(pointNX, point1.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(pointNX, point2.Y));
								linkPoints.push_back(winrt::Windows::Foundation::Point(point2.X, point2.Y));
							}
						}
					}
				}

				if (Spline2D::Smoothing)
				{
					linkPoints = Spline2D::GetSpline(linkPoints);
				}
			}
		}
	}
}

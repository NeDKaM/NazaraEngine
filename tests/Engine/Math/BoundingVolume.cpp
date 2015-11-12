#include <Nazara/Math/BoundingVolume.hpp>
#include <Catch/catch.hpp>

SCENARIO("BoundingVolume", "[MATH][BOUNDINGVOLUME]")
{
	GIVEN("With a null bounding volume and an infinite")
	{
		Nz::BoundingVolumef nullVolume = Nz::BoundingVolumef::Null();
		Nz::BoundingVolumef infiniteVolume = Nz::BoundingVolumef::Infinite();

		WHEN("We compare them")
		{
			THEN("They should be different")
			{
				REQUIRE(nullVolume != infiniteVolume);
			}
		}

		WHEN("We ask for the characteristic")
		{
			THEN("They should be respectively null and infinite")
			{
				CHECK(nullVolume.IsNull());
				CHECK(infiniteVolume.IsInfinite());
			}
		}

		WHEN("If we multiply them")
		{
			THEN("They should still be different")
			{
				nullVolume *= 5.f;
				infiniteVolume = infiniteVolume * 0.5f;

				REQUIRE(nullVolume != infiniteVolume);

				AND_WHEN("We ask for the characteristic (infinite and null)")
				{
					THEN("They should still be respectively null and infinite")
					{
						CHECK(nullVolume.IsNull());
						CHECK(infiniteVolume.IsInfinite());
					}
				}
			}
		}

		WHEN("We compare two null or two infinite")
		{
			THEN("Everything should be ok")
			{
				REQUIRE(Nz::BoundingVolumef::Null() == Nz::BoundingVolumef::Null());
				REQUIRE(Nz::BoundingVolumef::Infinite() == Nz::BoundingVolumef::Infinite());
			}
		}
	}

	GIVEN("Two same bounding volume with different constructor")
	{
		Nz::BoundingVolumef firstCenterAndUnit(0.f, 0.f, 0.f, 1.f, 1.f, 1.f);
		Nz::BoundingVolumef secondCenterAndUnit(Nz::Vector3f::Zero(), Nz::Vector3f::Unit());
		firstCenterAndUnit.Update(Nz::Matrix4f::Identity());
		secondCenterAndUnit.Update(Nz::Matrix4f::Identity());

		WHEN("We compare them")
		{
			THEN("Then the should be equal")
			{
				REQUIRE(firstCenterAndUnit == secondCenterAndUnit);
			}
		}

		WHEN("We ask for the characteristic")
		{
			THEN("They should be finite")
			{
				CHECK(firstCenterAndUnit.IsFinite());
				CHECK(secondCenterAndUnit.IsFinite());
			}
		}

		WHEN("We use a constructor of conversion")
		{
			THEN("There's no problem")
			{
				Nz::BoundingVolume<int> intVolumeCenterAndUnit(Nz::Boxi(Nz::Vector3i::Zero(), Nz::Vector3i::Unit()));
				Nz::BoundingVolumef thirdCenterAndUnit(intVolumeCenterAndUnit);
				REQUIRE(thirdCenterAndUnit == secondCenterAndUnit);
			}
		}

		WHEN("We make one twice bigger with a matrix")
		{
			firstCenterAndUnit.Update(Nz::Matrix4f::Scale(Nz::Vector3f::Unit() * 2.f));

			THEN("The local box should be the same but the aabb different")
			{
				REQUIRE(firstCenterAndUnit.obb.localBox == secondCenterAndUnit.obb.localBox);
				REQUIRE(firstCenterAndUnit.aabb != secondCenterAndUnit.aabb);
			}
		}
	}
}
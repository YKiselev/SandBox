#include "gtest/gtest.h"
#include "SbCore/AppConfiguration.h"

using namespace app;
using namespace sb_spi;

TEST(AppConfiguration, Dummy)
{
	AppConfiguration cfg;
	IntValue iv{ 100 };
	UllongValue ullv{ 0xffffff };
	DoubleValue dv{ 3.14 };
	FloatValue fv{ 3.14f };
	BoolValue bv{ true };
	StringValue sv{ 20, "Test" };

	ASSERT_TRUE(cfg.add("amount", iv));
	ASSERT_TRUE(cfg.add("color", ullv));
	ASSERT_TRUE(cfg.add("pi", dv));
	ASSERT_TRUE(cfg.add("velocity", fv));
	ASSERT_TRUE(cfg.add("flag", bv));
	ASSERT_TRUE(cfg.add("name", sv));

	ASSERT_EQ(100, cfg.getInt("amount"));
	ASSERT_EQ(0xffffff, cfg.getUllong("color"));
	ASSERT_NEAR(3.14, cfg.getDouble("pi"), 0.1);
	ASSERT_NEAR(3.14f, cfg.getFloat("velocity"), 0.1);
	ASSERT_TRUE(cfg.getBool("flag"));

	char buf[20];
	ASSERT_EQ(4, cfg.getString("name", buf, 20));
	ASSERT_EQ("Test", std::string{ buf });

	cfg.setInt("amount", 10);
	cfg.setUllong("color", 0xfefefe);
	cfg.setDouble("pi", 6.78);
	cfg.setFloat("velocity", 1.23f);
	cfg.setBool("flag", false);
	cfg.setString("name", "xyz");

	ASSERT_EQ(10, cfg.getInt("amount"));
	ASSERT_EQ(0xfefefe, cfg.getUllong("color"));
	ASSERT_NEAR(6.78, cfg.getDouble("pi"), 0.1);
	ASSERT_NEAR(1.23f, cfg.getFloat("velocity"), 0.1);
	ASSERT_FALSE(cfg.getBool("flag"));

	ASSERT_TRUE(cfg.remove("name"));
	ASSERT_TRUE(cfg.remove("amount"));
}
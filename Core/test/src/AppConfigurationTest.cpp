#include "gtest/gtest.h"
#include "SbCore/AppConfiguration.h"

using namespace app;
using namespace sb_spi;

TEST(AppConfiguration, Dummy)
{
	AppConfiguration cfg;
	IntValue iv{ "amount", 100 };
	UllongValue ullv{ "color", 0xffffff };
	DoubleValue dv{ "pi", 3.14 };
	FloatValue fv{ "velocity", 3.14f };
	BoolValue bv{ "flag", true };
	StringValue sv{ "name", 20, "Test" };

	ASSERT_TRUE(cfg.add(iv));
	ASSERT_TRUE(cfg.add(ullv));
	ASSERT_TRUE(cfg.add(dv));
	ASSERT_TRUE(cfg.add(fv));
	ASSERT_TRUE(cfg.add(bv));
	ASSERT_TRUE(cfg.add(sv));

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

	ASSERT_TRUE(cfg.remove(sv));
	ASSERT_TRUE(cfg.remove(iv));
}
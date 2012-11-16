#include "rules/redundant/RedundantIfStatementRule.cpp"

TEST(RedundantIfStatementRuleTest, PropertyTest)
{
    RedundantIfStatementRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("redundant if statement", rule.name());
}

TEST(RedundantIfStatementRuleTest, GoodIfStatement)
{
    testRuleOnCode(new RedundantIfStatementRule(), "void aMethod() { if (1) {;} }");
}

TEST(RedundantIfStatementRuleTest, IfStatementWithOneThenAndZeroElse)
{
    testRuleOnCode(new RedundantIfStatementRule(), "int aMethod() { if (1) { return 1; } else return 0; }",
        0, 1, 17, 1, 50);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithZeroThenAndOneElse)
{
    testRuleOnCode(new RedundantIfStatementRule(), "int aMethod() { if (1) return 0; else { return 1; } }",
        0, 1, 17, 1, 51);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithTrueThenAndFalseElse)
{
    testRuleOnCXXCode(new RedundantIfStatementRule(), "bool aMethod() { if (1) { return true; } else return false; }",
        0, 1, 18, 1, 54);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithFalseThenAndTrueElse)
{
    testRuleOnCXXCode(new RedundantIfStatementRule(), "bool aMethod() { if (1) return false; else { return true; } }",
        0, 1, 18, 1, 59);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithYesThenAndNoElse)
{
    testRuleOnObjCCode(new RedundantIfStatementRule(), "\n\
typedef signed char    BOOL;    \n\
#define YES             (BOOL)1 \n\
#define NO              (BOOL)0 \n\
BOOL aMethod() { if (1) { return YES; } else return NO; }", 0, 5, 18, 5, 53);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithNoThenAndYesElse)
{
    testRuleOnObjCCode(new RedundantIfStatementRule(), "\n\
typedef signed char    BOOL;    \n\
#define YES             (BOOL)1 \n\
#define NO              (BOOL)0 \n\
BOOL aMethod() { if (1) return NO; else { return YES; } }", 0, 5, 18, 5, 55);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithCIntDeclaration) // TODO: Need serious reconsideration on this
{
    testRuleOnCode(new RedundantIfStatementRule(), "void aMethod() { int b; if (1) { b = 6; } else b = 0; }",
        0, 1, 25, 1, 52);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithCppBooleanDeclaration)
{
    testRuleOnCXXCode(new RedundantIfStatementRule(), "void aMethod() { bool b; if (1) { b = true; } else b = false; }",
        0, 1, 26, 1, 56);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithObjCBOOLDeclaration)
{
    testRuleOnObjCCode(new RedundantIfStatementRule(), "\n\
typedef signed char    BOOL;    \n\
#define YES             (BOOL)1 \n\
#define NO              (BOOL)0 \n\
void aMethod() { BOOL b; if (1) { b = YES; } else b = NO; }", 0, 5, 26, 5, 55);
}

TEST(RedundantIfStatementRuleTest, IfStatementWithSameBooleanReturn)
{
    testRuleOnObjCCode(new RedundantIfStatementRule(), "\n\
typedef signed char    BOOL;    \n\
#define YES             (BOOL)1 \n\
#define NO              (BOOL)0 \n\
void aMethod() { BOOL b; if (1) { b = YES; } else b = YES; }");
}

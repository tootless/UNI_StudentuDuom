#include <gtest/gtest.h>
#include "../Studentas.h"

TEST(CalcTests, VidurkisTest) {
    std::vector<double> paz = { 8, 9, 10 };

    double rez = calc_vidurkis(paz);

    EXPECT_DOUBLE_EQ(rez, 9.0);
}

TEST(CalcTests, MedianaOddTest) {
    std::vector<double> paz = { 10, 8, 9 };

    double rez = calc_mediana(paz);

    EXPECT_DOUBLE_EQ(rez, 9.0);
}

TEST(CalcTests, MedianaEvenTest) {
    std::vector<double> paz = { 10, 8, 6, 4 };

    double rez = calc_mediana(paz);

    EXPECT_DOUBLE_EQ(rez, 7.0);
}

TEST(StudentasTests, ReadStudentTest) {
    std::istringstream input("Jonas Jonaitis 8 9 10");

    Studentas s(input);

    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPavarde(), "Jonaitis");
    EXPECT_EQ(s.getEgzaminas(), 10);
    EXPECT_EQ(s.getPazymiaiSize(), 2);
}

TEST(StudentasTests, GalutinisVidurkisTest) {
    Studentas s;

    s.addPazymys(8);
    s.addPazymys(10);
    s.setEgzaminas(9);

    double rez = s.getGalutinis(calc_vidurkis);

    EXPECT_DOUBLE_EQ(rez, 9.0); //(8+10)/2 = 9, rez turetu buti = 0.4 * 9 + 0.6 * 9 = 9.0
}

TEST(StudentasTests, OutputOperatorTest) {
    Studentas s;

    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.addPazymys(10);
    s.addPazymys(8);
    s.setEgzaminas(9);

    std::ostringstream out;

    out << s;

    std::string result = out.str();

    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Jonas"), std::string::npos);
    EXPECT_NE(result.find("Jonaitis"), std::string::npos);
}

//
// RULE OF FIVE TESTAI
//

TEST(RuleOfFiveTests, CopyConstructorTest) {
    Studentas s1;

    s1.setVardas("Petras");
    s1.setPavarde("Petraitis");
    s1.addPazymys(10);
    s1.setEgzaminas(9);

    Studentas s2(s1);

    EXPECT_EQ(s2.getVardas(), "Petras");
    EXPECT_EQ(s2.getPavarde(), "Petraitis");
    EXPECT_EQ(s2.getEgzaminas(), 9);
    EXPECT_EQ(s2.getPazymiaiSize(), 1);
}

TEST(RuleOfFiveTests, MoveConstructorTest) {
    Studentas s1;

    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    s1.addPazymys(8);
    s1.setEgzaminas(10);

    Studentas s2(std::move(s1));

    EXPECT_EQ(s2.getVardas(), "Jonas");
    EXPECT_EQ(s2.getPavarde(), "Jonaitis");
    EXPECT_EQ(s2.getEgzaminas(), 10);
}

TEST(RuleOfFiveTests, CopyAssignmentTest) {
    Studentas s1;

    s1.setVardas("Aiste");
    s1.setPavarde("Aistaite");
    s1.addPazymys(9);
    s1.setEgzaminas(8);

    Studentas s2;

    s2 = s1;

    EXPECT_EQ(s2.getVardas(), "Aiste");
    EXPECT_EQ(s2.getPavarde(), "Aistaite");
    EXPECT_EQ(s2.getEgzaminas(), 8);
}

TEST(RuleOfFiveTests, MoveAssignmentTest) {
    Studentas s1;

    s1.setVardas("Mantas");
    s1.setPavarde("Mantaitis");
    s1.addPazymys(7);
    s1.setEgzaminas(9);

    Studentas s2;

    s2 = std::move(s1);

    EXPECT_EQ(s2.getVardas(), "Mantas");
    EXPECT_EQ(s2.getPavarde(), "Mantaitis");
    EXPECT_EQ(s2.getEgzaminas(), 9);
}
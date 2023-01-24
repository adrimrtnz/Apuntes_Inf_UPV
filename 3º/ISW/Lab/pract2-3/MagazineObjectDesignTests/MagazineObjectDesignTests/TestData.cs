using Magazine.Entities;
using System;

namespace MagazineObjectDesignTests
{
    public class TestData
    {
        //GENERIC
        public static int EXPECTED_EMPTY_LIST_COUNT = 0;
        public static int EXPECTED_ONE_ELEMENT_LIST_COUNT = 1;

        //PERSON
        public static string EXPECTED_PERSON_ID = "11111111A";
        public static string EXPECTED_PERSON_NAME = "Nombre1";
        public static string EXPECTED_PERSON_SURNAME = "Apellido1";

        //USER
        public static bool EXPECTED_USER_ALERTED = false;
        public static string EXPECTED_USER_AREASOFINTEREST = "Área1";
        public static string EXPECTED_USER_EMAIL = "user1@gmail.com";
        public static string EXPECTED_USER_LOGIN = "user1";
        public static string EXPECTED_USER_PASSWORD = "p1111";

        //AREA
        public static string EXPECTED_AREA_NAME = "Área1";
        public static User EXPECTED_AREA_EDITOR = new User(EXPECTED_PERSON_ID, EXPECTED_PERSON_NAME, EXPECTED_PERSON_SURNAME, EXPECTED_USER_ALERTED, EXPECTED_USER_AREASOFINTEREST, EXPECTED_USER_EMAIL, EXPECTED_USER_LOGIN, EXPECTED_USER_PASSWORD);
        public static Magazine.Entities.Magazine EXPECTED_AREA_MAGAZINE = new Magazine.Entities.Magazine(EXPECTED_MAGAZINE_NAME, EXPECTED_AREA_EDITOR);

        //MAGAZINE
        public static string EXPECTED_MAGAZINE_NAME = "Magazine1";
        public static User EXPECTED_MAGAZINE_CHIEFEDITOR = new User(EXPECTED_PERSON_ID, EXPECTED_PERSON_NAME, EXPECTED_PERSON_SURNAME, EXPECTED_USER_ALERTED, EXPECTED_USER_AREASOFINTEREST, EXPECTED_USER_EMAIL, EXPECTED_USER_LOGIN, EXPECTED_USER_PASSWORD);

        //ISSUE
        public static int EXPECTED_ISSUE_NUMBER = 120;
        public static DateTime EXPECTED_PUBLICATION_DATE = DateTime.Parse("2023-10-10");
        public static Magazine.Entities.Magazine EXPECTED_MAGAZINE = new Magazine.Entities.Magazine(EXPECTED_MAGAZINE_NAME,EXPECTED_MAGAZINE_CHIEFEDITOR);

        //PAPER
        public static string EXPECTED_PAPER_TITLE = "Paper1";
        public static DateTime EXPECTED_PAPER_UPLOADDATE = DateTime.Parse("2022-10-10");
        public static User EXPECTED_PAPER_RESPONSIBLE = new User(EXPECTED_PERSON_ID, EXPECTED_PERSON_NAME, EXPECTED_PERSON_SURNAME, EXPECTED_USER_ALERTED, EXPECTED_USER_AREASOFINTEREST, EXPECTED_USER_EMAIL, EXPECTED_USER_LOGIN, EXPECTED_USER_PASSWORD);
        public static Area EXPECTED_PAPER_AREA = new Area(EXPECTED_AREA_NAME, EXPECTED_AREA_EDITOR, EXPECTED_AREA_MAGAZINE);

        //EVALUATION
        public static bool EXPECTED_EVALUATION_ACCEPTED = false;
        public static string EXPECTED_EVALUATION_COMMENTS = "Comments of paper";
        public static DateTime EXPECTED_EVALUATION_DATE= DateTime.Parse("2022-10-10");

   



    }
}
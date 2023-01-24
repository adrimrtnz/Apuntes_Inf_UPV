using Magazine.Entities;
using System;


namespace MagazinePersistenceTests
{
    public class TestData
    {
        //GENERIC
        public static int EXPECTED_EMPTY_LIST_COUNT = 0;
        public static int EXPECTED_ONE_ELEMENT_LIST_COUNT = 1;

        //PERSON
        public static string EXPECTED_PERSON_ID = "11111111P";
        public static string EXPECTED_PERSON_NAME = "NombrePerson1";
        public static string EXPECTED_PERSON_SURNAME = "ApellidoPerson1";

        //USER
        public static string EXPECTED_USER_ID = "11111111U";
        public static string EXPECTED_USER_NAME = "NombreUser1";
        public static string EXPECTED_USER_SURNAME = "ApellidoUser1";
        public static bool EXPECTED_USER_ALERTED = false;
        public static string EXPECTED_USER_AREASOFINTEREST = "햞ea1";
        public static string EXPECTED_USER_EMAIL = "user1@gmail.com";
        public static string EXPECTED_USER_LOGIN = "user1";
        public static string EXPECTED_USER_PASSWORD = "p1111";
        
        public static string EXPECTED_USER2_ID = "22222222B";
        public static string EXPECTED_USER2_NAME = "NombreUser2";
        public static string EXPECTED_USER2_SURNAME = "ApellidoUser2";
        public static bool EXPECTED_USER2_ALERTED = false;
        public static string EXPECTED_USER2_AREASOFINTEREST = "햞ea1";
        public static string EXPECTED_USER2_EMAIL = "user2@gmail.com";
        public static string EXPECTED_USER2_LOGIN = "user2";
        public static string EXPECTED_USER2_PASSWORD = "p2222";

        
        public static string EXPECTED_CHIEF_ID = "33333333C";
        public static string EXPECTED_CHIEF_NAME = "Chief Editor Name";
        public static string EXPECTED_CHIEF_SURNAME = "Chief Editor Last Name";
        public static bool EXPECTED_CHIEF_ALERTED = false;
        public static string EXPECTED_CHIEF_AREASOFINTEREST = "햞ea3";
        public static string EXPECTED_CHIEF_EMAIL = "chief@gmail.com";
        public static string EXPECTED_CHIEF_LOGIN = "chief";
        public static string EXPECTED_CHIEF_PASSWORD = "p3333";
        //AREA
        public static string EXPECTED_AREA_NAME = "햞ea1";
        
        //MAGAZINE
        public static string EXPECTED_MAGAZINE_NAME = "Magazine1";


        //ISSUE
        public static int EXPECTED_ISSUE_NUMBER = 1;

        //PAPER
        public static string EXPECTED_PAPER_TITLE = "Paper1";
        public static DateTime EXPECTED_PAPER_UPLOADDATE = DateTime.Parse("2022-10-10");
        //  public static User EXPECTED_PAPER_RESPONSIBLE = new User(EXPECTED_PERSON_ID, EXPECTED_PERSON_NAME, EXPECTED_PERSON_SURNAME, EXPECTED_USER_ALERTED, EXPECTED_USER_AREASOFINTEREST, EXPECTED_USER_EMAIL, EXPECTED_USER_LOGIN, EXPECTED_USER_PASSWORD);
        
        //EVALUATION
        public static bool EXPECTED_EVALUATION_ACCEPTED = false;
        public static string EXPECTED_EVALUATION_COMMENTS = "Comments of paper";
        public static DateTime EXPECTED_EVALUATION_DATE = DateTime.Parse("2022-10-10");


    }
}
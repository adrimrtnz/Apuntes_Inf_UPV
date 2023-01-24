using Magazine.Entities;
using Magazine.Persistence;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;

namespace MagazinePersistenceTests
{
   [TestClass]
    public class PaperTest: BaseTest
    {
        [TestMethod]
        public void StoresInitialData()
        {

            User user = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);

            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);
            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);
            Paper paper = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, area, user);
            dal.Insert(paper);
            dal.Commit();

            Paper paperDAL = dal.GetAll<Paper>().First();
            Assert.AreEqual(TestData.EXPECTED_PAPER_TITLE, paperDAL.Title, "Title not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_PAPER_UPLOADDATE, paperDAL.UploadDate, "UploadDate not properly stored.");
            Assert.AreEqual(area, paperDAL.BelongingArea, "BelongingArea not properly stored.");

            Assert.IsNotNull(paperDAL.CoAuthors, "Collection of CoAuthors not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, paperDAL.CoAuthors.Count, "Collection of CoAuthors not properly initialized. \n The list should have one element (the Main Author is also a CoAuthor).\n");
            
        }

        [TestMethod]
        public void StoresDataWithRelations()
        {
            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);
            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);

            Issue issue = new Issue(TestData.EXPECTED_ISSUE_NUMBER, area.Magazine);
            dal.Insert(issue);
            dal.Commit();

            User user = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);
            Paper paper = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, area, user);
            dal.Insert(paper);
            dal.Commit();

            Evaluation eval = new Evaluation(TestData.EXPECTED_EVALUATION_ACCEPTED, TestData.EXPECTED_EVALUATION_COMMENTS, TestData.EXPECTED_EVALUATION_DATE);
            area.Papers.Add(paper);
            area.EvaluationPending.Add(paper);
            paper.EvaluationPendingArea = area;
            paper.PublicationPendingArea = area;
            area.PublicationPending.Add(paper);
            paper.Evaluation = eval;

            issue.PublishedPapers.Add(paper);
            paper.Issue = issue;
            dal.Commit();


            Paper paperDAL = dal.GetAll<Paper>().First();
            Assert.AreEqual(TestData.EXPECTED_PAPER_TITLE, paperDAL.Title, "Title not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_PAPER_UPLOADDATE, paperDAL.UploadDate, "UploadDate not properly stored.");
            Assert.AreEqual(area, paperDAL.BelongingArea, "BelongingArea not properly stored.");
            Assert.AreEqual(area, paperDAL.EvaluationPendingArea, "EvaluationPendingArea not properly stored.");
            Assert.AreEqual(area, paperDAL.PublicationPendingArea, "PublicationPendingArea not properly stored.");
            Assert.AreEqual(user, paperDAL.Responsible, "Responsible not properly stored.");
            Assert.IsNotNull(paperDAL.CoAuthors, "Collection of CoAuthors not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, paperDAL.CoAuthors.Count(), "Collection of CoAuthors not properly initialized. \n The list should have one element\n");
            Assert.AreEqual(user, paperDAL.CoAuthors.FirstOrDefault(), "CoAuthors relationship not properly created.");
            Assert.AreEqual(eval, paperDAL.Evaluation, "Evaluation not properly stored.");
            Assert.AreEqual(issue, paperDAL.Issue, "Issue not properly stored.");            
        }
    }
}
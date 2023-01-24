using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Reflection;
using Magazine.Entities;

namespace MagazineObjectDesignTests
{
    [TestClass]
    public class PaperTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {
            PropertyInfo property = typeof(Paper).GetProperty("CoAuthors");
            Assert.IsTrue(property.GetMethod.IsVirtual, "CoAuthors property should be declared virtual.");
            property = typeof(Paper).GetProperty("Responsible");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Responsible property should be declared virtual.");
            property = typeof(Paper).GetProperty("BelongingArea");
            Assert.IsTrue(property.GetMethod.IsVirtual, "BelongingArea property should be declared virtual.");
            property = typeof(Paper).GetProperty("EvaluationPendingArea");
            Assert.IsTrue(property.GetMethod.IsVirtual, "EvaluationPendingArea property should be declared virtual.");
            property = typeof(Paper).GetProperty("PublicationPendingArea");
            Assert.IsTrue(property.GetMethod.IsVirtual, "PublicationPendingArea property should be declared virtual.");
            property = typeof(Paper).GetProperty("Evaluation");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Evaluation property should be declared virtual.");
            property = typeof(Paper).GetProperty("Issue");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Issue property should be declared virtual.");
        }
        [TestMethod]
        public void NoParamsConstructorInitializesCollections()
        {
            Paper paper = new Paper();
            Assert.AreNotSame(null, paper, "There must be a constructor without parameters.");
            Assert.IsNotNull(paper.CoAuthors, "Collection of CoAuthors not properly initialized. \n Patch the problem adding:  CoAuthors = new List<Person>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, paper.CoAuthors.Count, "Collection of CoAuthors not properly initialized. \n The list should be empty\n");
        }

        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Paper paper = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, TestData.EXPECTED_PAPER_AREA, TestData.EXPECTED_PAPER_RESPONSIBLE);
            Assert.AreEqual(TestData.EXPECTED_PAPER_TITLE, paper.Title, "Title not properly initialized.Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PAPER_UPLOADDATE, paper.UploadDate, "UploadDate not properly initialized. Please check if you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PAPER_AREA, paper.BelongingArea, "BelongingArea not properly initialized. Please check if you have correctly assigned the parameters in the corresponding class.");

            Assert.IsNotNull(paper.CoAuthors, "Collection of CoAuthors no properly initialized. \n Patch the problem adding:  :this() to constructor with parameters");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, paper.CoAuthors.Count, "Collection of CoAuthors not properly initialized. \n The list should have one element (the Main Author is also a CoAuthor).\n");
           
        }
    }
}

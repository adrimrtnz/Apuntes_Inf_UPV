using Magazine.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MagazinePersistenceTests
{
    [TestClass]
    public class EvaluationTest:BaseTest
    {
        [TestMethod]
        public void StoresInitialData()
        {
            Evaluation eval = new Evaluation(TestData.EXPECTED_EVALUATION_ACCEPTED, TestData.EXPECTED_EVALUATION_COMMENTS, TestData.EXPECTED_EVALUATION_DATE);
            dal.Insert(eval);
            dal.Commit();

            Evaluation evalDAL = dal.GetAll<Evaluation>().First();
            Assert.AreEqual(TestData.EXPECTED_EVALUATION_ACCEPTED, evalDAL.Accepted, "Accepted not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EVALUATION_COMMENTS, evalDAL.Comments, "Comments not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EVALUATION_DATE, evalDAL.Date, "Date not properly stored.");           

        }

        [TestMethod]
        public void StoresDataWithRelations()
        { 
        }
    }
}

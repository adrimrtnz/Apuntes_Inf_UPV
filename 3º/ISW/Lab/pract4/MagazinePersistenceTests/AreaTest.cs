using Magazine.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Magazine.Persistence;

namespace MagazinePersistenceTests
{
    
    [TestClass]
    public class AreaTest:BaseTest
    {
        private static bool HasInverseAnnotation(PropertyInfo property)
        {
            var attributes = property.GetCustomAttributes(false);
            Attribute[] attrs = System.Attribute.GetCustomAttributes(property);
            return attrs.Any((attr) =>
            {
                return attr is InversePropertyAttribute;
            });

        }

        [TestMethod]
        public void StoresInitialData()
        {
            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);

            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);
            //TestData.EXPECTED_AREA_EDITOR.Area = area;
            //TestData.EXPECTED_AREA_MAGAZINE.Areas.Add(area);
            dal.Insert(area);
            dal.Commit();

            Area areaDAL = dal.GetAll<Area>().First();
            Assert.AreEqual(TestData.EXPECTED_AREA_NAME, areaDAL.Name, "Area not properly stored.");
            
            
            Assert.AreEqual(editor, areaDAL.Editor, "Editor not properly stored.");
            Assert.AreEqual(magazine, areaDAL.Magazine, "Magazine not properly stored.");
            
            Assert.IsNotNull(areaDAL.Papers, "Collection of Papers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, areaDAL.Papers.Count, "Collection of Papers not properly initialized. \n The list should be empty\n");

            Assert.IsNotNull(areaDAL.PublicationPending, "Collection of PublicationPending not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, areaDAL.PublicationPending.Count, "Collection of PublicationPending not properly initialized. \n The list should be empty\n");

            Assert.IsNotNull(areaDAL.EvaluationPending, "Collection of EvaluationPending not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, areaDAL.EvaluationPending.Count, "Collection of EvaluationPending not properly initialized. \n The list should be empty\n");

        }

        [TestMethod]
        public void StoresDataWithRelations()
        {
            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);

            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);
            //TestData.EXPECTED_AREA_EDITOR.Area = area;
            //TestData.EXPECTED_AREA_MAGAZINE.Areas.Add(area);
            dal.Insert(area);
            dal.Commit();
            Assert.IsTrue(HasInverseAnnotation(typeof(Area).GetProperty("Papers")), "Property Papers should have Data Annotation [InverseProperty(\"BelongingArea\")]");
            Assert.IsTrue(HasInverseAnnotation(typeof(Area).GetProperty("EvaluationPending")), "Property EvaluationPending should have Data Annotation [InverseProperty(\"EvaluationPendingArea\")]");
            Assert.IsTrue(HasInverseAnnotation(typeof(Area).GetProperty("PublicationPending")), "Property PublicationPending should have Data Annotation [InverseProperty(\"PublicationPendingArea\")]");
            User responsible = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, 
                TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);


            Paper p = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, area, responsible);
            area.EvaluationPending.Add(p);
            area.PublicationPending.Add(p);
            area.Papers.Add(p);
            dal.Commit();

            Area areaDAL = dal.GetAll<Area>().First();
            Assert.IsNotNull(areaDAL.Papers, "Collection of Papers not properly stored.");
            Assert.AreEqual(p, areaDAL.Papers.FirstOrDefault(), "Papers relationship not properly created.");
            Assert.IsNotNull(areaDAL.EvaluationPending, "Collection of EvaluationPending not properly stored.");
            Assert.AreEqual(p, areaDAL.EvaluationPending.FirstOrDefault(), "EvaluationPending relationship not properly created.");
            Assert.IsNotNull(areaDAL.PublicationPending, "Collection of PublicationPending not properly stored.");
            Assert.AreEqual(p, areaDAL.PublicationPending.FirstOrDefault(), "PublicationPending relationship not properly stored.");
        }
    }
}

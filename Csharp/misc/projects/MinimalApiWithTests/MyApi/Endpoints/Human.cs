namespace MyApi.Endpoints
{
    public static class Human
    {
        public static void Get(string filePath)
        {
            filePath = Path.GetFullPath(filePath);
            if (!File.Exists(filePath))
            {

            }
        }
    }
}

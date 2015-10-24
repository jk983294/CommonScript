public class jackson_convertor {

    @POST
    @Path("/a/{param}/c")
    @Consumes(MediaType.APPLICATION_JSON)
    public Response updateNavPerformances(@PathParam("param") Integer param, String postPayload) throws Exception {
        /**
         * java.util.Date doesn’t has the time zone concept, if you print a Date object,
         * it will always display the date with the system default time zone.
         * so we need to adjust to service timezone
         * Jackson defaults to using GMT for all processing unless specifically told otherwise.
         * this parameter fix also neat
         * -Duser.timezone=America/New_York
         */
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        dateFormat.setTimeZone(TimeZone.getTimeZone("EST"));
        ObjectMapper mapper = new ObjectMapper();
        mapper.getDeserializationConfig().setDateFormat(dateFormat);
        List<MyObject> myObjects = mapper.readValue(postPayload, new TypeReference<List<MyObject>>(){});
        myService.updateMyObject(myObjects, param);
        return Response.status(201).entity("update success").build();
    }

}